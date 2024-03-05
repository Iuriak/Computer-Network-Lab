/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2015 Sébastien Deronne
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Sébastien Deronne <sebastien.deronne@gmail.com>
 */

#include "ns3/core-module.h"
#include "ns3/applications-module.h"
#include "ns3/wifi-module.h"
#include "ns3/mobility-module.h"
#include "ns3/internet-module.h"
#include "ns3/netanim-module.h"
#include "string"
#include "sstream"
// This example considers two hidden stations in an 802.11n network which supports MPDU aggregation.
// The user can specify whether RTS/CTS is used and can set the number of aggregated MPDUs.
// modified by jinweizu
// Example: ./waf --run "wifi-hidden-stations --enableRts=1 --nMpdus=8"
//
// Network topology:
//
//   Wifi 192.168.1.0
//
//        receiver
//   *    *    *
//   |    |    |
//   n1   n2   n3
//
// Packets in this simulation aren't marked with a QosTag so they are considered
// belonging to BestEffort Access Class (AC_BE).

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("WifiHiddenStations");
//mody
int main (int argc, char *argv[])
{
  LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
  LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);

  uint32_t payloadSize = 1472; //bytes
  uint64_t simulationTime = 10; //seconds
  uint32_t nMpdus = 1;
  uint32_t maxAmpduSize = 0;
  bool enableRts = 1;//0,off,1:on
  double minExpectedThroughput = 0;
  double maxExpectedThroughput = 0;

  CommandLine cmd;
  cmd.AddValue ("nMpdus", "Number of aggregated MPDUs", nMpdus);
  cmd.AddValue ("payloadSize", "Payload size in bytes", payloadSize);
  cmd.AddValue ("enableRts", "Enable RTS/CTS", enableRts);
  cmd.AddValue ("simulationTime", "Simulation time in seconds", simulationTime);
  cmd.AddValue ("minExpectedThroughput", "if set, simulation fails if the lowest throughput is below this value", minExpectedThroughput);
  cmd.AddValue ("maxExpectedThroughput", "if set, simulation fails if the highest throughput is above this value", maxExpectedThroughput);
  cmd.Parse (argc, argv);
  std::string title("无线局域网--隐藏节点实验项目:Rst:On");
  if (!enableRts)
    {
      Config::SetDefault ("ns3::WifiRemoteStationManager::RtsCtsThreshold", StringValue ("999999"));
      title="无线局域网--隐藏节点实验项目:Rst:Off";
    }
  else
    {
      Config::SetDefault ("ns3::WifiRemoteStationManager::RtsCtsThreshold", StringValue ("0"));
    }

  //Set the maximum size for A-MPDU with regards to the payload size
  maxAmpduSize = nMpdus * (payloadSize + 200);

  // Set the maximum wireless range to 5 meters in order to reproduce a hidden nodes scenario, i.e. the distance between hidden stations is larger than 5 meters
  Config::SetDefault ("ns3::RangePropagationLossModel::MaxRange", DoubleValue (50));//5

  NodeContainer wifiStaNodes;
  wifiStaNodes.Create (3);
  //NodeContainer wifiApNode;
  //wifiApNode.Create (1);

  YansWifiChannelHelper channel = YansWifiChannelHelper::Default ();
  channel.AddPropagationLoss ("ns3::RangePropagationLossModel"); //wireless range limited to 50 meters!

  YansWifiPhyHelper phy = YansWifiPhyHelper();//::Default 
  phy.SetPcapDataLinkType (WifiPhyHelper::DLT_IEEE802_11_RADIO);
  phy.SetChannel (channel.Create ());

  WifiHelper wifi;
  wifi.SetStandard (WIFI_STANDARD_80211n);// WIFI_PHY_STANDARD_80211n_5GHZ
  wifi.SetRemoteStationManager ("ns3::ConstantRateWifiManager", "DataMode", StringValue ("HtMcs7"), "ControlMode", StringValue ("HtMcs0"));
  WifiMacHelper mac;
  Ssid ssid = Ssid ("simple-mpdu-aggregation");
  mac.SetType ("ns3::AdhocWifiMac",
               "Ssid", SsidValue (ssid),
               "BE_MaxAmpduSize", UintegerValue (maxAmpduSize));

  NetDeviceContainer staDevices;
  staDevices = wifi.Install (phy, mac, wifiStaNodes);

  //mac.SetType ("ns3::ApWifiMac",
  //             "Ssid", SsidValue (ssid),
  //             "EnableBeaconJitter", BooleanValue (false),
  //             "BE_MaxAmpduSize", UintegerValue (maxAmpduSize));

  //NetDeviceContainer apDevice;
  //apDevice = wifi.Install (phy, mac, wifiApNode);

  // Setting mobility model
  MobilityHelper mobility;
  //Ptr<ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator> ();

  // AP is between the two stations, each station being located at 5 meters from the AP.
  // The distance between the two stations is thus equal to 10 meters.
  // Since the wireless range is limited to 5 meters, the two stations are hidden from each other.
  /*positionAlloc->Add (Vector (0.0, 0.0, 0.0));
  positionAlloc->Add (Vector (5.0, 0.0, 0.0));
  positionAlloc->Add (Vector (10.0, 0.0, 0.0));
  mobility.SetPositionAllocator (positionAlloc);*/

  mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  //mobility.Install (wifiApNode);
  mobility.Install (wifiStaNodes);
  /*
   * added b jwz
   */
  NodeContainer titleNodes;
  titleNodes.Create(1);
  mobility.Install(titleNodes);
  AnimationInterface::SetConstantPosition(wifiStaNodes.Get(0),0,50);
  AnimationInterface::SetConstantPosition(wifiStaNodes.Get(1),50,50);
  AnimationInterface::SetConstantPosition(wifiStaNodes.Get(2),100,50);
  AnimationInterface::SetConstantPosition(titleNodes.Get(0),50,10);

  // Internet stack
  InternetStackHelper stack;
  //stack.Install (wifiApNode);
  stack.Install (wifiStaNodes);

  Ipv4AddressHelper address;
  address.SetBase ("192.168.1.0", "255.255.255.0");
  Ipv4InterfaceContainer StaInterface;
  StaInterface = address.Assign (staDevices);
  //Ipv4InterfaceContainer ApInterface;
  //ApInterface = address.Assign (apDevice);

  // Setting applications
  uint16_t port = 9;
  UdpServerHelper server (port);
  ApplicationContainer serverApp = server.Install (wifiStaNodes.Get(1));
  serverApp.Start (Seconds (0.0));
  serverApp.Stop (Seconds (simulationTime + 1));

  UdpClientHelper client (StaInterface.GetAddress (1), port);
  client.SetAttribute ("MaxPackets", UintegerValue (4294967295u));
  client.SetAttribute ("Interval", TimeValue (Time ("0.05"))); //packets/s,0.00002
  client.SetAttribute ("PacketSize", UintegerValue (payloadSize));
  UdpClientHelper client2 (StaInterface.GetAddress (1), port);
  client2.SetAttribute ("MaxPackets", UintegerValue (4294967295u));
  client2.SetAttribute ("Interval", TimeValue (Time ("0.10"))); //packets/s,0.00002
  client2.SetAttribute ("PacketSize", UintegerValue (payloadSize));

  // Saturated UDP traffic from stations to AP
  ApplicationContainer clientApp1 = client.Install (wifiStaNodes.Get(0));
  //ApplicationContainer clientApp2 = client.Install (wifiStaNodes.Get(2));
  ApplicationContainer clientApp2 = client2.Install (wifiStaNodes.Get(2));
  clientApp1.Start (Seconds (1.0));
  clientApp1.Stop (Seconds (simulationTime + 1));
  clientApp2.Start (Seconds (1.10));//1.01
  clientApp2.Stop (Seconds (simulationTime + 1));

  phy.EnablePcap ("WifiHiddenStations_Sta1", staDevices.Get (0));
  phy.EnablePcap ("WifiHiddenStations_Recv", staDevices.Get (1));
  phy.EnablePcap ("WifiHiddenStations_Sta2", staDevices.Get (2));

  Simulator::Stop (Seconds (simulationTime + 1));
  // Create the xml file of this cc file
  AnimationInterface anim ("xml/lab-wifi-hidden-stations.xml");
  /*
   * added by jwz
   */
  uint32_t resourceLogo= anim.AddResource("/home/network/tarballs/ns-allinone-3.28/ns-3.28/scratch/tongji.png");
  uint32_t resourcePhone = anim.AddResource("/home/network/tarballs/ns-allinone-3.28/ns-3.28/scratch/phone.png");
  anim.UpdateNodeDescription(3,title);
  anim.UpdateNodeImage(3,resourceLogo);
  anim.UpdateNodeSize(3,12,12);
  //std::stringstream ss;
  char str[40];
  for (uint32_t i = 0; i < wifiStaNodes.GetN (); ++i)
     {
	   sprintf(str,"STA:Node:%d",wifiStaNodes.Get (i)->GetId());
       anim.UpdateNodeDescription (wifiStaNodes.Get (i), str);
       anim.UpdateNodeColor (wifiStaNodes.Get (i), 255, 0, 0);
       //jwz
       anim.UpdateNodeImage(i, resourcePhone);
       anim.UpdateNodeSize(i, 6, 6);
     }
  anim.UpdateNodeDescription(wifiStaNodes.Get(1),"Recv:Node:1");
  anim.UpdateNodeColor(wifiStaNodes.Get(1),0,255,0);
  //for (uint32_t i = 0; i < wifiApNode.GetN (); ++i)
  //   {
  //     anim.UpdateNodeDescription (wifiApNode.Get (i), "AP");
  //     anim.UpdateNodeColor (wifiApNode.Get (i), 0, 255, 0);
  //   }
  anim.EnableWifiMacCounters (Seconds (0), Seconds (10));
  anim.EnableWifiPhyCounters (Seconds (0), Seconds (10));

  AsciiTraceHelper ascii;
//string nameStr=name;
 // string traceFile=nameStr+".tr";
  Ptr<OutputStreamWrapper> stream=ascii.CreateFileStream("hidden.tr");
  //for(unsigned int i=0;i<3;i++){
	  //wifiStaNodes.Get(i).EnableAsciiAll(stream);
//mEthernet[i].EnablePcapAll (name, true);
  //}
  phy.EnableAsciiAll(stream);
  Simulator::Run ();
  Simulator::Destroy ();

  uint32_t totalPacketsThrough = DynamicCast<UdpServer> (serverApp.Get (0))->GetReceived ();
  double throughput = totalPacketsThrough * payloadSize * 8 / (simulationTime * 1000000.0);
  std::cout << "Throughput: " << throughput << " Mbit/s" << '\n';
  if (throughput < minExpectedThroughput || (maxExpectedThroughput > 0 && throughput > maxExpectedThroughput))
    {
      NS_LOG_ERROR ("Obtained throughput " << throughput << " is not in the expected boundaries!");
      exit (1);
    }
  return 0;
}

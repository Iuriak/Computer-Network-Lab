#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/mobility-module.h"
#include "ns3/lte-module.h"
#include "ns3/applications-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/config-store-module.h"
#include "ns3/netanim-module.h"
#include "math.h"


using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("lte-ex-3");
void
NotifyConnectionEstablishedUe (std::string context,
                               uint64_t imsi,
                               uint16_t cellid,
                               uint16_t rnti)
{
  std::cout << "Time:" << Simulator::Now ().GetSeconds () << " " << context
            << " UE IMSI " << imsi
            << ": connected to CellId " << cellid
            << " with RNTI " << rnti
            << std::endl;
}

void
NotifyHandoverStartUe (std::string context,
                       uint64_t imsi,
                       uint16_t cellid,
                       uint16_t rnti,
                       uint16_t targetCellId)
{
  std::cout << "Time:" << Simulator::Now ().GetSeconds () << " " << context
            << " UE IMSI " << imsi
            << ": previously connected to CellId " << cellid
            << " with RNTI " << rnti
            << ", doing handover to CellId " << targetCellId
            << std::endl;
}

void
NotifyHandoverEndOkUe (std::string context,
                       uint64_t imsi,
                       uint16_t cellid,
                       uint16_t rnti)
{
  std::cout << "Time:" << Simulator::Now ().GetSeconds () << " " << context
            << " UE IMSI " << imsi
            << ": successful handover to CellId " << cellid
            << " with RNTI " << rnti
            << std::endl;
}

void
NotifyConnectionReconfigurationUe (std::string context,
                       uint64_t imsi,
                       uint16_t cellid,
                       uint16_t rnti)
{
  std::cout << "Time:" << Simulator::Now ().GetSeconds () << " " << context
            << " UE IMSI " << imsi
            << ": connection reconfiguration to CellId " << cellid
            << " with RNTI " << rnti
            << std::endl;
}

void
NotifyHandoverEndErrorUe (std::string context,
                       uint64_t imsi,
                       uint16_t cellid,
                       uint16_t rnti)
{
  std::cout << "Time:" << Simulator::Now ().GetSeconds () << " " << context
            << " UE IMSI " << imsi
            << ": failed handover to CellId " << cellid
            << " with RNTI " << rnti
            << std::endl;
}

void
NotifyConnectionEstablishedEnb (std::string context,
                                uint64_t imsi,
                                uint16_t cellid,
                                uint16_t rnti)
{
  std::cout << "Time:" << Simulator::Now ().GetSeconds () << " " << context
            << " eNB CellId " << cellid
            << ": successful connection of UE with IMSI " << imsi
            << " RNTI " << rnti
            << std::endl;
}

void
NotifyHandoverStartEnb (std::string context,
                        uint64_t imsi,
                        uint16_t cellid,
                        uint16_t rnti,
                        uint16_t targetCellId)
{
  std::cout << "Time:" << Simulator::Now ().GetSeconds () << " " << context
            << " eNB CellId " << cellid
            << ": start handover of UE with IMSI " << imsi
            << " RNTI " << rnti
            << " to CellId " << targetCellId
            << std::endl;
}

void
NotifyHandoverEndOkEnb (std::string context,
                        uint64_t imsi,
                        uint16_t cellid,
                        uint16_t rnti)
{
  std::cout << "Time:" << Simulator::Now ().GetSeconds () << " " << context
            << " eNB CellId " << cellid
            << ": completed handover of UE with IMSI " << imsi
            << " RNTI " << rnti
            << std::endl;
}


void
NotifyConnectionReconfigurationEnb (std::string context,
                       uint64_t imsi,
                       uint16_t cellid,
                       uint16_t rnti)
{
  std::cout << "Time:" << Simulator::Now ().GetSeconds () << " " << context
            << " eNB CellId " << cellid
            << ": connection reconfiguration with IMSI " << imsi
            << " with RNTI " << rnti
            << std::endl;
}

int main(int argc, char *argv[])
{

  //LogComponentEnable("UdpClient",LOG_LEVEL_INFO);
  //LogComponentEnable("PacketSink",LOG_LEVEL_INFO);
  //LogComponentEnable ("lte-x2-test", LOG_LEVEL_LOGIC);
  //LogComponentEnable ("LteEnbPhy", LOG_LEVEL_LOGIC);
  //old
  //LogComponentEnable ("LteEnbRrc", LOG_LEVEL_INFO);
  LogComponentEnable ("LteUeRrc", LOG_LEVEL_INFO);
 //define related params
  //jwz
  int distanceUnit=48;//48
  double gridSize=24000.0;//500.0;900：8；24000:1
  double gridWidth=5.0;//4.0
  //ue number
  uint16_t numberOfUes = 1;
  //enb number
  //uint16_t numberOfEnbs = 16;
  uint16_t numberOfEnbs = 15;

  //packet trans interval/ms
  double interPacketInterval = 100;
  //length of time
  double simTime = 4;
  //moving speed of ue
  //double movingSpeedOfUes = 300.0;
 double movingSpeedOfUes = 500.0*distanceUnit;
 bool useCa = false;
  //dl ul
  bool disableDl = false;
  bool disableUl = false;
  bool disablePl = false;


  //algorithm type，以RSRP为度量标准
  //std::string handoverAlgo = "A3";
  //A2A4以RSRQ为度量标准
  std::string handoverAlgo = "A2A4";
  //attri of A3 algorithm
  //double hysteresis = 1.0;
  double hysteresis = 0.0;

  //attri of A3 algorithm
  //uint16_t timeToTrigger = 64;
  uint16_t timeToTrigger = 0;
  //attri of A2A4 algorithm
  uint16_t servingCellThreshold = 30;
  //attri of A2A4 algorithm
  uint16_t neighbourCellOffset = 1;

  //tx power of the enbs
  //all enb have same tx power
  //double enbTxPowerDbm = 46.0;
  double enbTxPowerDbm = 12.5;
  //noiseFigure of the enbs
  //double noiseFigure = 5.0;
  double noiseFigure = 1.25;
  //macToChannelDelay of enbs
  uint16_t macToChannelDelay = 2;
  //moving direction of ue
  std::string direction = "right";

  // Command line arguments
  CommandLine cmd;
  cmd.AddValue("simTime", "Total duration of the simulation /seconds", simTime);
  cmd.AddValue("numberOfUes", "Number of the enbs", numberOfUes);
  cmd.AddValue("numberOfEnbs", "Number of the enbs", numberOfEnbs);
  cmd.AddValue("movingSpeedOfUes", "Moving speed of the ues", movingSpeedOfUes);
  cmd.AddValue ("useCa", "Whether to use carrier aggregation.", useCa);
  cmd.AddValue ("disableDl", "Disable downlink data flows", disableDl);
  cmd.AddValue ("disableUl", "Disable uplink data flows", disableUl);
  cmd.AddValue ("disablePl", "Disable data flows between peer UEs", disablePl);

  cmd.AddValue("enbTxPowerDbm", "TX power  used by HeNBs /dbm", enbTxPowerDbm);
  cmd.AddValue("handoverAlgo", "type of  handover algorithm(A3 orA2A4)", handoverAlgo);
  cmd.AddValue("hysteresis", "hysteresis of A3 algorithm", hysteresis);
  cmd.AddValue("timeToTrigger", "timeToTrigger of A3 algorithm", timeToTrigger);
  cmd.AddValue("neighbourCellOffset", "neighbourCellOffset of A2A4 algorithm", neighbourCellOffset);
  cmd.AddValue("servingCellThreshold", "servingCellThreshold of A2A4 algorithm", servingCellThreshold);
  cmd.AddValue("noiseFigure", "Loss (dB) in the Signal-to-Noise-Ratio due to  non-idealities in the receiver", noiseFigure);
  cmd.AddValue("macToChannelDelay", "The delay in TTI units that occurs between a scheduling decision in the MAC and the actual start of the transmission by the PHY", macToChannelDelay);
  cmd.AddValue("direction","moving direction of ue:up,down,left,right or random",direction);
  // cmd.AddValue("", "", );
  // cmd.AddValue("", "", );
  cmd.Parse(argc, argv);

  //any other attributes needed can be config like above
  //and make it work like below 

//attributes and their description and default value can be found in 
//   /src/lte/model/a2-a4-rsrq-handover-algorithm.cc
//   /src/lte/model/a3-rsrq-handover-algorithm.cc
//  /src/lte/model/lte-enb-phy.cc
//  /src/lte/model/lte-enb-mac.cc
//  /src/lte/model/lte-ue-phy.cc
//  /src/lte/model/lte-ue-mac.cc
//  /src/lte/model/lte-ue-power-control.cc
//and so on 

  // change some default attributes
  Config::SetDefault("ns3::UdpClient::Interval", TimeValue(MilliSeconds(10)));
  Config::SetDefault("ns3::UdpClient::MaxPackets", UintegerValue(1000000));
  Config::SetDefault("ns3::LteHelper::UseIdealRrc", BooleanValue(true));
  //change some physic attribute about lte
  Config::SetDefault("ns3::LteEnbPhy::TxPower", DoubleValue(enbTxPowerDbm));
  Config::SetDefault("ns3::LteEnbPhy::NoiseFigure", DoubleValue(noiseFigure));
  Config::SetDefault("ns3::LteEnbPhy::MacToChannelDelay", UintegerValue(macToChannelDelay));
  if (useCa)
   {
     Config::SetDefault ("ns3::LteHelper::UseCa", BooleanValue (useCa));
     Config::SetDefault ("ns3::LteHelper::NumberOfComponentCarriers", UintegerValue (2));
     Config::SetDefault ("ns3::LteHelper::EnbComponentCarrierManager", StringValue ("ns3::RrComponentCarrierManager"));
   }
  //and so on

  Ptr<LteHelper> lteHelper = CreateObject<LteHelper>();
  Ptr<PointToPointEpcHelper> epcHelper = CreateObject<PointToPointEpcHelper>();
  lteHelper->SetEpcHelper(epcHelper);

  lteHelper->SetSchedulerType("ns3::RrFfMacScheduler");
  if (handoverAlgo == "A2A4")
  {
    lteHelper->SetHandoverAlgorithmType("ns3::A2A4RsrqHandoverAlgorithm");
    lteHelper->SetHandoverAlgorithmAttribute("ServingCellThreshold",
                                             UintegerValue(servingCellThreshold));
    lteHelper->SetHandoverAlgorithmAttribute("NeighbourCellOffset",
                                             UintegerValue(neighbourCellOffset));
  }else{
	  //set some attribute of A3 algorithm
	  lteHelper->SetHandoverAlgorithmType("ns3::A3RsrpHandoverAlgorithm");
	  lteHelper->SetHandoverAlgorithmAttribute("Hysteresis",
	                                           DoubleValue(hysteresis));
	  lteHelper->SetHandoverAlgorithmAttribute("TimeToTrigger",
	                                           TimeValue(MilliSeconds(timeToTrigger)));

  }
  //get pgw node
  Ptr<Node> pgw = epcHelper->GetPgwNode();

  // Create a single RemoteHost
  NodeContainer remoteHostContainer;
  remoteHostContainer.Create(1);
  Ptr<Node> remoteHost = remoteHostContainer.Get(0);
  InternetStackHelper internet;
  internet.Install(remoteHostContainer);

  //create ue and enb nodes
  NodeContainer ueNodes;
  NodeContainer enbNodes;
  enbNodes.Create(numberOfEnbs);
  ueNodes.Create(numberOfUes);

  //lym:dynamicly adjust moving range,网格列数
  /*int sqrtResult = (int)sqrt((double)numberOfEnbs);
  if (sqrtResult * sqrtResult != numberOfEnbs)
    sqrtResult = sqrtResult + 1;
  double xRange = (double)sqrtResult * 500;
  double yRange = (double)sqrtResult * 500;*/
  double xRange = gridWidth * gridSize;
  //error
  //double yRange = (int)(numberOfEnbs/gridWidth) * gridSize;
  double yRange = gridWidth* gridSize;

  // set position of enbs
  // lym:change the layout of enbs
  MobilityHelper enbMobility;
  enbMobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
  enbMobility.SetPositionAllocator("ns3::GridPositionAllocator",
                                   "LayoutType", StringValue("RowFirst"),
                                   "MinX", DoubleValue(0.0),
                                   "MinY", DoubleValue(2*gridSize),
                                   "DeltaX", DoubleValue(gridSize),
                                   "DeltaY", DoubleValue(gridSize),
                                   "GridWidth", UintegerValue(gridWidth));//UintegerValue(sqrtResult)
  enbMobility.Install(enbNodes);

  //set position of pgw
  MobilityHelper pgwMobility;
  pgwMobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
  pgwMobility.SetPositionAllocator("ns3::GridPositionAllocator", "MinX", DoubleValue(gridSize), "MinY",
                                   DoubleValue(gridSize));
  pgwMobility.Install(pgw);
  //set position of remote host
  MobilityHelper remoteHostMobility;
  remoteHostMobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
  remoteHostMobility.SetPositionAllocator("ns3::GridPositionAllocator", "MinX", DoubleValue(3*gridSize), "MinY",
                                          DoubleValue(gridSize));
  remoteHostMobility.Install(remoteHostContainer);
  //jwz
  NodeContainer titleNodes;
  titleNodes.Create(1);
  MobilityHelper titleMobility;
  titleMobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
  titleMobility.SetPositionAllocator("ns3::GridPositionAllocator", "MinX", DoubleValue(0.0), "MinY",
                                   DoubleValue(0.0));
  titleMobility.Install(titleNodes);
  uint16_t titleNodeNo= numberOfEnbs+numberOfUes+2;


  //make ue move
  //lym:random position initialize
  MobilityHelper ueMobility;
  std::string x_="750.0";
  std::string y_="750.0";
  std::string direction_="ns3::UniformRandomVariable[Min=0.0|Max=6.283184]";
  if(direction=="up"){
	x_="750.0";
  	y_="1500.0";
	direction_="ns3::UniformRandomVariable[Min=4.6|Max=4.6]";
  }else if(direction=="down"){
	x_="750.0";
	y_="0.0";
   	direction_="ns3::UniformRandomVariable[Min=1.5|Max=1.5]";
  }else if(direction=="left"){
	x_="1500.0";
	y_="750.0";
	direction_="ns3::UniformRandomVariable[Min=3.1|Max=3.1]";
  }else if(direction=="right"){
	x_="0.0";
	y_="36460.0";
	direction_="ns3::UniformRandomVariable[Min=0.0|Max=0.0]";
  }


  ueMobility.SetPositionAllocator("ns3::RandomDiscPositionAllocator",
                                  "X", StringValue(x_),
                                  "Y", StringValue(y_),
                                  "Rho", StringValue("ns3::UniformRandomVariable[Min=0.0|Max=0.0]"),
                                  "Theta", StringValue("ns3::UniformRandomVariable[Min=0.0|Max=0.0]"));
  // ueMobility.SetMobilityModel("ns3::WaypointMobilityModel");
  //lym:random move model
  //lym:modifiable moving speed
  char speedStr[100];
  char str[40];
  sprintf(speedStr, "ns3::UniformRandomVariable[Min=%f|Max=%f]", movingSpeedOfUes, movingSpeedOfUes);
  ueMobility.SetMobilityModel("ns3::RandomWalk2dMobilityModel",
                              "Mode", EnumValue(RandomWalk2dMobilityModel::MODE_TIME),
                                "Distance", DoubleValue (gridSize*gridWidth),
                              //"Time", TimeValue(Seconds(1.0)),
                              "Direction", StringValue(direction_),
                              "Speed", StringValue(speedStr),
                              "Bounds", RectangleValue(Rectangle(0.0, xRange, 0.0, yRange)));
  ueMobility.Install(ueNodes);


  // Install LTE Devices in eNB and UEs
  Config::SetDefault("ns3::LteEnbPhy::TxPower", DoubleValue(enbTxPowerDbm));
  NetDeviceContainer enbLteDevs = lteHelper->InstallEnbDevice(enbNodes);
  NetDeviceContainer ueLteDevs = lteHelper->InstallUeDevice(ueNodes);

  // Install the IP stack on the UEs
  internet.Install(ueNodes);
  Ipv4InterfaceContainer ueIpIfaces;
  ueIpIfaces = epcHelper->AssignUeIpv4Address(NetDeviceContainer(ueLteDevs));

  // Create the Internet
  PointToPointHelper p2ph;
  p2ph.SetDeviceAttribute("DataRate", DataRateValue(DataRate("100Gb/s")));
  p2ph.SetDeviceAttribute("Mtu", UintegerValue(1500));
  p2ph.SetChannelAttribute("Delay", TimeValue(Seconds(0.010)));

  //let ue connect with remotehost
  //!not sure  link ue and remotehost or link pgw and remotehost  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  NetDeviceContainer internetDevices = p2ph.Install(pgw, remoteHost);
  //NetDeviceContainer internetDevices = p2ph.Install(ueNodes.Get(0), remoteHost);
  Ipv4AddressHelper ipv4h;
  ipv4h.SetBase("1.0.0.0", "255.0.0.0");
  Ipv4InterfaceContainer internetIpIfaces = ipv4h.Assign(internetDevices);
  Ipv4Address remoteHostAddr = internetIpIfaces.GetAddress(1);

  // Routing of the Internet Host (towards the LTE network)
  Ipv4StaticRoutingHelper ipv4RoutingHelper;
  Ptr<Ipv4StaticRouting> remoteHostStaticRouting = ipv4RoutingHelper.GetStaticRouting(remoteHost->GetObject<Ipv4>());
  // interface 0 is localhost, 1 is the p2p device
  remoteHostStaticRouting->AddNetworkRouteTo(Ipv4Address("7.0.0.0"), Ipv4Mask("255.0.0.0"), 1);

  // Set the default gateway for the UE
 // Ptr<Node> ue = ueNodes.Get(0);
 // Ptr<Ipv4StaticRouting> ueStaticRouting = ipv4RoutingHelper.GetStaticRouting(ue->GetObject<Ipv4>());
 // ueStaticRouting->SetDefaultRoute(epcHelper->GetUeDefaultGatewayAddress(), 1);

  for (uint32_t u = 0; u < ueNodes.GetN (); ++u)
  {
    Ptr<Node> ueNode = ueNodes.Get (u);
    // Set the default gateway for the UE
    Ptr<Ipv4StaticRouting> ueStaticRouting = ipv4RoutingHelper.GetStaticRouting (ueNode->GetObject<Ipv4> ());
    ueStaticRouting->SetDefaultRoute (epcHelper->GetUeDefaultGatewayAddress (), 1);
  }
  // Attach UEs to the first eNodeB
  for (uint16_t i = 0; i < ueNodes.GetN (); i++)
  {
    lteHelper->Attach (ueLteDevs.Get(i), enbLteDevs.Get(0));
    // side effect: the default EPS bearer will be activated
  }
 // lteHelper->Attach(ueLteDevs.Get(0), enbLteDevs.Get(0));

  // Install and start applications on UE and remote host
  NS_LOG_LOGIC ("setting up applications");

  uint16_t dlPort = 10000;
  uint16_t ulPort = 20000;
  uint16_t otherPort = 3000;

  //install applications
  ApplicationContainer clientApps;
  ApplicationContainer serverApps;
  for (uint32_t u = 0; u < ueNodes.GetN (); ++u)
    {
      if (!disableDl)
        {
	  NS_LOG_LOGIC ("installing UDP DL app for UE " << u);
          PacketSinkHelper dlPacketSinkHelper ("ns3::UdpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), dlPort));
          serverApps.Add (dlPacketSinkHelper.Install (ueNodes.Get (u)));

          UdpClientHelper dlClient (ueIpIfaces.GetAddress (u), dlPort);
          dlClient.SetAttribute ("Interval", TimeValue (MilliSeconds(interPacketInterval)));
          dlClient.SetAttribute ("MaxPackets", UintegerValue (1000000));
          clientApps.Add (dlClient.Install (remoteHost));
        }

      if (!disableUl)
        {
	  NS_LOG_LOGIC ("installing UDP UL app for UE " << u);
          ++ulPort;
          PacketSinkHelper ulPacketSinkHelper ("ns3::UdpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), ulPort));
          serverApps.Add (ulPacketSinkHelper.Install (remoteHost));

          UdpClientHelper ulClient (remoteHostAddr, ulPort);
          ulClient.SetAttribute ("Interval", TimeValue (MilliSeconds(interPacketInterval)));
          ulClient.SetAttribute ("MaxPackets", UintegerValue (1000000));
          clientApps.Add (ulClient.Install (ueNodes.Get(u)));
        }

      if (!disablePl && ueNodes.GetN() > 1)
        {
          NS_LOG_LOGIC ("installing UDP PL app for UE " << u);
          ++otherPort;
          PacketSinkHelper packetSinkHelper ("ns3::UdpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), otherPort));
          serverApps.Add (packetSinkHelper.Install (ueNodes.Get (u)));

          UdpClientHelper client (ueIpIfaces.GetAddress (u), otherPort);
          client.SetAttribute ("Interval", TimeValue (MilliSeconds(interPacketInterval)));
          client.SetAttribute ("MaxPackets", UintegerValue (1000000));
          clientApps.Add (client.Install (ueNodes.Get ((u + 1) % ueNodes.GetN())));
        }
    }

  serverApps.Start (MilliSeconds (500));
  clientApps.Start (MilliSeconds (500));

  // Add X2 inteface
  lteHelper->AddX2Interface(enbNodes);

  //enable some traces
  //lteHelper->EnableTraces ();
  lteHelper->EnablePhyTraces();
  lteHelper->EnableMacTraces();
  lteHelper->EnableRlcTraces();
  lteHelper->EnablePdcpTraces();
  //not known yet
  Ptr<RadioBearerStatsCalculator> rlcStats = lteHelper->GetRlcStats();
  rlcStats->SetAttribute("EpochDuration", TimeValue(Seconds(1.0)));
  Ptr<RadioBearerStatsCalculator> pdcpStats = lteHelper->GetPdcpStats();
  pdcpStats->SetAttribute("EpochDuration", TimeValue(Seconds(1.0)));

  //enable  pcap  traces save the data in /data
  //should create the folder first
  //p2ph.EnablePcapAll("data/lte-ex-3");

  // TASK2 ENABLE PCAP TRACING
  // related pcap files will be saved in /data
  //p2ph.EnablePcap("data/internetDevices", internetDevices);
  //p2ph.EnablePcap("data/enbLteDevs", enbLteDevs);
  //p2ph.EnablePcap("data/ueLteDevs", ueLteDevs);
  //p2ph.EnablePcap("data/enbNodes", enbNodes);
  //p2ph.EnablePcap("data/ueNodes", ueNodes);

  //animation
  //set the xml file name
  AnimationInterface anim("xml/lab-lte-handover.xml");

  //set some attributes
  anim.EnablePacketMetadata();
  //jwz
  //uint32_t node_num = numberOfEnbs+numberOfUes+2;
  //for(uint32_t i = 0; i < node_num; ++i)
  for(uint32_t i = 0; i < numberOfEnbs; ++i)
  {
    //anim.UpdateNodeSize (i, 20, 20);
    //jwz
    Ptr<LteEnbNetDevice> enbDevice=enbLteDevs.Get(i)->GetObject<LteEnbNetDevice>();
    uint16_t cellId=enbDevice->GetCellId();
    //char cellStr[40];
    sprintf(str,"Cell Id:%d",(unsigned int)cellId);
    anim.UpdateNodeDescription(enbNodes.Get(i),str);
  }
  anim.UpdateNodeDescription(ueNodes.Get(0),"UE");
  anim.UpdateNodeColor(ueNodes.Get(0), 255, 0, 0);

  anim.UpdateNodeDescription(remoteHost, "RemoteHost");
 // anim.UpdateNodeColor(remoteHost, 255, 0, 0);
  anim.UpdateNodeDescription(pgw, "SGW-PGW");
 //anim.UpdateNodeColor(pgw, 255, 0, 0);

  //Tower img resource
  uint32_t resourceTower;
  //Phone imig resource
  uint32_t resourcePhone;
  //Remote Host imig resource
  uint32_t resourceRemoteHost;
  //SGW-PGW imig resource
  uint32_t resourcePGW;

   //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!   img url should use absolute path   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  resourceTower = anim.AddResource("/home/user/tarballs/ns-allinone-3.28/ns-3.28/scratch/tower.png");//tower.png
  resourcePhone = anim.AddResource("/home/user/tarballs/ns-allinone-3.28/ns-3.28/scratch/phone.png");//phone.png
  resourceRemoteHost = anim.AddResource("/home/user/tarballs/ns-allinone-3.28/ns-3.28/scratch/remotehost.png");//remotehost.png
  resourcePGW = anim.AddResource("/home/user/tarballs/ns-allinone-3.28/ns-3.28/scratch/pgw.png");//pwg.png
  //jwz
  uint32_t resourceLte= anim.AddResource("/home/user/tarballs/ns-allinone-3.28/ns-3.28/scratch/lte.png");//lte.png
  anim.UpdateNodeDescription(titleNodeNo,"LTE-EPC蜂窝网络信元切换实验子项");
  anim.UpdateNodeImage(titleNodeNo,resourceLte);
  anim.UpdateNodeSize(titleNodeNo,300*distanceUnit,300*distanceUnit);
  anim.UpdateNodeImage(0, resourcePGW);
  anim.UpdateNodeSize(0, 300*distanceUnit, 300*distanceUnit);
  anim.UpdateNodeImage(1, resourceRemoteHost);
  anim.UpdateNodeSize(1, 400*distanceUnit, 400*distanceUnit);

  //lym:sfz:update tower img
  for (int i = 2; i < 2 + numberOfEnbs; i++)
  {
    anim.UpdateNodeImage(i, resourceTower);
    anim.UpdateNodeSize(i, 150*distanceUnit, 150*distanceUnit);
  }
  //lym:sfz:update phone img
  for (int i = 2 + numberOfEnbs; i < 2 + numberOfEnbs + numberOfUes; i++)
  {
    anim.UpdateNodeImage(i, resourcePhone);
    anim.UpdateNodeSize(i, 100*distanceUnit, 100*distanceUnit);
  }

 /** for(uint32_t i = 0; i < ueNodes.GetN(); ++i)
  {
    anim.UpdateNodeDescription(ueNodes.Get(i),"ue");
    anim.UpdateNodeColor(ueNodes.Get(i),0,255,0);
  }
  for(uint32_t i = 0; i < enbNodes.GetN(); ++i)
  {
    anim.UpdateNodeDescription(enbNodes.Get(i),"eNB");
    anim.UpdateNodeColor(enbNodes.Get(i),0,0,255);
  }**/

  // connect custom trace sinks for RRC connection establishment and handover notification



  Simulator::Stop(Seconds(simTime));
  Simulator::Run();
  Simulator::Destroy();
  return 0;
}

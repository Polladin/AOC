
#include "PacketDecoder.h"

#include "common/print_results.h"

int main()
{
  common::print_results< PacketDecoder >( "day_16", "Day 16: Packet Decoder", "1111111|1", "0|1" );

  std::cout << "Test str: " << "C200B40A82" << " result: " <<  PacketDecoder().test_task_2( "C200B40A82" ) << "\n";
  std::cout << "Test str: " << "04005AC33890" << " result: " <<  PacketDecoder().test_task_2( "04005AC33890" ) << "\n";
  std::cout << "Test str: " << "880086C3E88112" << " result: " <<  PacketDecoder().test_task_2( "880086C3E88112" ) << "\n";
  std::cout << "Test str: " << "CE00C43D881120" << " result: " <<  PacketDecoder().test_task_2( "CE00C43D881120" ) << "\n";
  std::cout << "Test str: " << "D8005AC2A8F0" << " result: " <<  PacketDecoder().test_task_2( "D8005AC2A8F0" ) << "\n";
  std::cout << "Test str: " << "F600BC2D8F" << " result: " <<  PacketDecoder().test_task_2( "F600BC2D8F" ) << "\n";
  std::cout << "Test str: " << "9C005AC2F8F0" << " result: " <<  PacketDecoder().test_task_2( "9C005AC2F8F0" ) << "\n";
  std::cout << "Test str: " << "9C0141080250320F1802104A08" << " result: " <<  PacketDecoder().test_task_2( "9C0141080250320F1802104A08" ) << "\n";
}

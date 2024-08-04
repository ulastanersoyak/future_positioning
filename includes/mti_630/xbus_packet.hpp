#ifndef XBUSPACKET_HPP
#define XBUSPACKET_HPP

#include <cstddef>
#include <cstdint>
#include <vector>

class XbusPacket
{
public:
  XbusPacket ();

  // Add a byte to the internal buffer and update state accordingly.
  void feedByte (uint8_t byte);

  // Check if a complete and valid packet has been received.
  bool isPacketComplete () const;

  // Check if the packet's checksum is valid.
  bool validateChecksum () const; // Make this method public.

  // Reset the state of the packet parser.
  void reset ();

  // Get the data bytes of the packet if it's complete and valid.
  std::vector<uint8_t> getData () const;
  const std::vector<uint8_t> &
  getRawData () const
  {
    return m_buffer;
  }

private:
  uint8_t computeChecksum (const std::vector<uint8_t> &packet) const;

  std::vector<uint8_t> m_buffer{};
  bool m_extendedLength{ false };
  std::size_t m_expectedLength{ 0 };
  bool m_lengthValid{
    false
  }; // New member to track the validity of m_expectedLength
};

#endif

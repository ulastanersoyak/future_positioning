#include "mti_630/mti_buffer.hpp"
#include "mti_630/mti_data_package.hpp"

void
parse_data (mti_data_package &xsdata, std::uint16_t data_id,
            std::vector<std::uint8_t> packet_data)
{
  switch (data_id)
    {
    case 0x1020:
      {
        xsdata.package_counter = static_cast<std::uint32_t> (
            (packet_data.at (0) << 8U) | packet_data.at (1));
        break;
      }

    case 0x1060:
      {
        xsdata.sample_fine_time = static_cast<std::uint32_t> (
            (packet_data.at (0) << 24U) | (packet_data.at (1) << 16U)
            | (packet_data.at (2) << 8U) | packet_data.at (3));
        break;
      }

    case 0x1010:
      {
        std::uint8_t hour = packet_data.at (8);
        std::uint8_t minute = packet_data.at (9);
        std::uint8_t second = packet_data.at (10);
        xsdata.time = utc (hour, minute, second);
        break;
      }

    case 0x2030:
      {
        // TODO: fix euler
        xsdata.euler.at (0) = ntohf (*(uint32_t *)&packet_data.at (0));
        xsdata.euler.at (1) = ntohf (*(uint32_t *)&packet_data.at (4));
        xsdata.euler.at (2) = ntohf (*(uint32_t *)&packet_data.at (8));
        break;
      }

    case 0x2010:
      {
        if (packet_data.size () == 16)
          {
            float *quat = (float *)packet_data.data ();
            xsdata.quat[0] = ntohf (*(uint32_t *)&quat[0]);
            xsdata.quat[1] = ntohf (*(uint32_t *)&quat[1]);
            xsdata.quat[2] = ntohf (*(uint32_t *)&quat[2]);
            xsdata.quat[3] = ntohf (*(uint32_t *)&quat[3]);
            xsdata.quaternionAvailable = true;
            xsdata
                .convert_quat_to_euler (); // Ensure this method is implemented
          }
        break;
      }

    case 0x4020:
      {
        if (packet_data.size () == 12)
          {
            xsdata.acc[0] = ntohf (*(uint32_t *)&packet_data[0]);
            xsdata.acc[1] = ntohf (*(uint32_t *)&packet_data[4]);
            xsdata.acc[2] = ntohf (*(uint32_t *)&packet_data[8]);
            xsdata.accAvailable = true;
          }
        break;
      }

    case 0x4030:
      {
        if (packet_data.size () == 12)
          {
            xsdata.freeacc[0] = ntohf (*(uint32_t *)&packet_data[0]);
            xsdata.freeacc[1] = ntohf (*(uint32_t *)&packet_data[4]);
            xsdata.freeacc[2] = ntohf (*(uint32_t *)&packet_data[8]);
            xsdata.freeaccAvailable = true;
          }
        break;
      }

    case 0x8020:
      {
        if (packet_data.size () == 12)
          {
            xsdata.rot[0] = ntohf (*(uint32_t *)&packet_data[0]);
            xsdata.rot[1] = ntohf (*(uint32_t *)&packet_data[4]);
            xsdata.rot[2] = ntohf (*(uint32_t *)&packet_data[8]);
            xsdata.rotAvailable = true;
          }
        break;
      }

    case 0xC020:
      {
        if (packet_data.size () == 12)
          {
            xsdata.mag[0] = ntohf (*(uint32_t *)&packet_data[0]);
            xsdata.mag[1] = ntohf (*(uint32_t *)&packet_data[4]);
            xsdata.mag[2] = ntohf (*(uint32_t *)&packet_data[8]);
            xsdata.magAvailable = true;
          }
        break;
      }

    case 0x5042:
      {
        if (packet_data.size () == 12)
          {
            xsdata.latlon[0] = get_data_fp1632 (packet_data, 0);
            xsdata.latlon[1] = get_data_fp1632 (packet_data, 6);
            xsdata.latlonAvailable = true;
          }
        break;
      }

    case 0x5022:
      {
        if (packet_data.size () == 6)
          {
            xsdata.altitude = get_data_fp1632 (packet_data, 0);
            xsdata.altitudeAvailable = true;
          }
        break;
      }

    case 0xE020:
      {
        if (packet_data.size () == 4)
          {
            xsdata.statusWord = (packet_data[0] << 24) | (packet_data[1] << 16)
                                | (packet_data[2] << 8) | packet_data[3];
            xsdata.statusWordAvailable = true;
          }
        break;
      }

    case 0xD012:
      {
        if (packet_data.size () == 18)
          {
            xsdata.vel[0] = get_data_fp1632 (packet_data, 0);
            xsdata.vel[1] = get_data_fp1632 (packet_data, 6);
            xsdata.vel[2] = get_data_fp1632 (packet_data, 12);
            xsdata.velocity
          }

        static mti_data_package parse_buffer (const mti_buffer &mti_buf)
        {
          mti_data_package xsdata;
          std::vector<uint8_t> data_part{ mti_buf.buffer.begin () + 4,
                                          mti_buf.buffer.end () - 1 };
          std::uint32_t bytes_offset = 0;

          while (bytes_offset < data_part.size ())
            {
              auto data_id
                  = static_cast<std::uint16_t> ((data_part[bytes_offset] << 8U)
                                                | data_part[bytes_offset + 1]);

              std::uint8_t data_len = data_part[bytes_offset + 2];
              std::vector<std::uint8_t> packet_data (
                  data_part.begin () + bytes_offset + 3,
                  data_part.begin () + bytes_offset + 3 + data_len);

              parse_data (xsdata, data_id, packet_data);
              bytes_offset
                  += data_len + 3; // 2 bytes for id, 1 byte for length
            }
          return xsdata;
        }

        [[nodiscard]] bool mti_buffer::is_buffer_complete () const
        {
          if (!is_length_valid)
            {
              return false;
            }

          size_t total_length = 3 + 1 + expected_length + 1;
          return buffer.size () == total_length;
        }

        [[nodiscard]] std::optional<std::uint8_t>
        mti_buffer::compute_checksum () const
        {
          if (buffer.size () < 2)
            {
              return std::nullopt;
            }
          std::uint8_t checksum = 0;
          for (size_t i = 1; i < buffer.size (); ++i)
            {
              checksum += buffer[i];
            }
          return checksum;
        }

        [[nodiscard]] bool mti_buffer::validate_checksum () const
        {
          if (!is_buffer_complete ())
            {
              return false;
            }

          auto checksum = compute_checksum ();
          if (!checksum.has_value ())
            {
              return false;
            }

          return checksum.value () == buffer.back ();
        }

        void mti_buffer::reset () noexcept
        {
          buffer.clear ();
          is_extended_length = false;
          expected_length = 0;
          is_length_valid = false;
          got_first_byte = false;
          got_second_byte = false;
        }

        void mti_buffer::feed_byte (std::uint8_t byte) noexcept
        {
          if (buffer.empty () && byte == 0xFA)
            {
              buffer.push_back (byte);
              got_first_byte = true;
              return;
            }

          if (got_first_byte && !got_second_byte)
            {
              if (byte == 0xFF)
                {
                  buffer.push_back (byte);
                  got_second_byte = true;
                }
              else
                {
                  this->reset ();
                }
              return;
            }

          if (got_first_byte && got_second_byte && buffer.size () == 2)
            {
              if (byte == 0x36)
                {
                  buffer.push_back (byte);
                }
              else
                {
                  reset ();
                }
              return;
            }

          if (got_first_byte && got_second_byte && buffer.size () >= 3)
            {
              buffer.push_back (byte);

              if (buffer.size () == 4)
                {
                  expected_length = byte;
                  is_length_valid = true;
                }

              if (is_buffer_complete ())
                {
                  reset ();
                }
            }
        }

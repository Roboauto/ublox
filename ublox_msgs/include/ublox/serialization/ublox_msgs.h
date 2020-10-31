//==============================================================================
// Copyright (c) 2012, Johannes Meyer, TU Darmstadt
// All rights reserved.

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the Flight Systems and Automatic Control group,
//       TU Darmstadt, nor the names of its contributors may be used to
//       endorse or promote products derived from this software without
//       specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//==============================================================================


#ifndef UBLOX_SERIALIZATION_UBLOX_MSGS_H
#define UBLOX_SERIALIZATION_UBLOX_MSGS_H
#ifdef _MSC_VER
using uint = unsigned int;
#endif


#include <ublox/serialization.h>
#include <ublox_msgs/ublox_msgs.h>
#include <cstring>

namespace ublox::serialization {
    class IStream {
    public:
        IStream(const uint8_t *data, uint size): data_(data), size_(size) {

        }

        template <typename T>
        void next(T& toWrite) {
            static_assert(std::is_fundamental<T>::value, "Type must be fundamental");
            memcpy(&toWrite, &data_[ptr_], sizeof(T));
            ptr_ += sizeof(T);
        }

        template <typename T, std::size_t SIZE>
        void next(std::array<T,SIZE>& toWrite) {
            memcpy(toWrite.data(), &data_[ptr_], SIZE * sizeof(T));
            ptr_ += SIZE * sizeof(T);
        }

        void next(bool& toWrite) {
            uint8_t b;
            memcpy(&b, &data_[ptr_], 1);
            toWrite = static_cast<bool>(b);
            ptr_ += 1;
        }

        const uint8_t * data() const {
            return data_+ ptr_;
        }

        uint size() const {
            return size_ - ptr_;
        }

        void shift(uint x) {
            ptr_ += x;
        }

    protected:
        const uint8_t *data_{};
        uint size_{};
        uint ptr_{0};
    };

    class OStream {
    public:
        OStream(uint8_t *data, uint size) : data_(data), size_(size) {

        }

        template <typename T>
        void next(const T& toRead) {
            static_assert(std::is_fundamental<T>::value, "Type must be fundamental");
            memcpy(&data_[ptr_], &toRead, sizeof(T));
            ptr_ += sizeof(T);
        }

        template <typename T, std::size_t SIZE>
        void next(const std::array<T,SIZE>& toWrite) {
            memcpy(&data_[ptr_], toWrite.data(), SIZE * sizeof(T));
            ptr_ += SIZE * sizeof(T);
        }

        void next(const bool& toRead) {
            uint8_t b = static_cast<uint8_t>(toRead);
            memcpy(&data_[ptr_], &b, 1);
            ptr_ += 1;
        }

        uint8_t * data() {
            return data_+ ptr_;
        }

        uint size() const{
            return size_ - ptr_;
        }

        void shift(uint x) {
            ptr_ += x;
        }

    protected:
        uint8_t *data_{};
        uint size_{};
        uint ptr_{0};
    };

    template<class T>
    void deserialize(ublox::serialization::IStream& istream, T& data) {
        static_assert(!std::is_same_v<T, unsigned int>, "Ne");
        auto serializedSize = Serializer<T>::serializedLength(data);
        Serializer<T>::read(istream.data(), istream.size(), data);
        istream.shift(serializedSize);
    }

    template<class T>
    void serialize(ublox::serialization::OStream& ostream, const T& data) {
        auto serializedSize = Serializer<T>::serializedLength(data);
        Serializer<T>::write(ostream.data(), ostream.size(), data);
        ostream.shift(serializedSize);
    }
}

///
/// This file declares custom serializers for u-blox messages with dynamic 
/// lengths and messages where the get/set messages have different sizes, but
/// share the same parameters, such as CfgDAT.
///

namespace ublox {

///
/// @brief Serializes the CfgDAT message which has a different length for 
/// get/set.
///
template <>
struct Serializer<ublox_msgs::CfgDAT> {
  typedef boost::call_traits<ublox_msgs::CfgDAT> CallTraits;
  static void read(const uint8_t *data, uint32_t count, 
                   typename CallTraits::reference m) {
    ublox::serialization::IStream stream(const_cast<uint8_t *>(data), count);
    stream.next(m.datumNum);
    stream.next(m.datumName);
    stream.next(m.majA);
    stream.next(m.flat);
    stream.next(m.dX);
    stream.next(m.dY);
    stream.next(m.dZ);
    stream.next(m.rotX);
    stream.next(m.rotY);
    stream.next(m.rotZ);
    stream.next(m.scale);
  }

  static uint32_t serializedLength (typename CallTraits::param_type) {
    // this is the size of CfgDAT set messages
    // serializedLength is only used for writes so this is ok
    return 44;
  }

  static void write(uint8_t *data, uint32_t size, 
                    typename CallTraits::param_type m) {
    ublox::serialization::OStream stream(data, size);
    // ignores datumNum & datumName
    stream.next(m.majA);
    stream.next(m.flat);
    stream.next(m.dX);
    stream.next(m.dY);
    stream.next(m.dZ);
    stream.next(m.rotX);
    stream.next(m.rotY);
    stream.next(m.rotZ);
    stream.next(m.scale);
  }
};

template <>
struct Serializer<ublox_msgs::CfgGNSS_Block> {
    typedef boost::call_traits<ublox_msgs::CfgGNSS_Block> CallTraits;
    static void read(const uint8_t *data, uint32_t count,
                     typename CallTraits::reference m) {
        ublox::serialization::IStream stream(const_cast<uint8_t *>(data), count);
        stream.next(m.gnssId);
        stream.next(m.resTrkCh);
        stream.next(m.maxTrkCh);
        stream.next(m.reserved1);
        stream.next(m.flags);
    }

    static uint32_t serializedLength (typename CallTraits::param_type) {
        return sizeof(ublox_msgs::CfgGNSS_Block);
    }

    static void write(uint8_t *data, uint32_t size,
                      typename CallTraits::param_type m) {
        ublox::serialization::OStream stream(data, size);
        // ignores datumNum & datumName
        stream.next(m.gnssId);
        stream.next(m.resTrkCh);
        stream.next(m.maxTrkCh);
        stream.next(m.reserved1);
        stream.next(m.flags);
    }
};

template <>
struct Serializer<ublox_msgs::CfgRST> {
    typedef boost::call_traits<ublox_msgs::CfgRST> CallTraits;
    static void read(const uint8_t *data, uint32_t count,
                     typename CallTraits::reference m) {
        ublox::serialization::IStream stream(const_cast<uint8_t *>(data), count);
        stream.next(m.navBbrMask);
        stream.next(m.resetMode);
        stream.next(m.reserved1);
    }

    static uint32_t serializedLength (typename CallTraits::param_type) {
        return sizeof(ublox_msgs::CfgRST);
    }

    static void write(uint8_t *data, uint32_t size,
                      typename CallTraits::param_type m) {
        ublox::serialization::OStream stream(data, size);
        stream.next(m.navBbrMask);
        stream.next(m.resetMode);
        stream.next(m.reserved1);
    }
};

template <>
struct Serializer<ublox_msgs::UpdSOS> {
    typedef boost::call_traits<ublox_msgs::UpdSOS> CallTraits;
    static void read(const uint8_t *data, uint32_t count,
                     typename CallTraits::reference m) {
        ublox::serialization::IStream stream(const_cast<uint8_t *>(data), count);
        stream.next(m.cmd);
        stream.next(m.reserved1);
    }

    static uint32_t serializedLength (typename CallTraits::param_type) {
        return sizeof(ublox_msgs::UpdSOS);
    }

    static void write(uint8_t *data, uint32_t size,
                      typename CallTraits::param_type m) {
        ublox::serialization::OStream stream(data, size);
        stream.next(m.cmd);
        stream.next(m.reserved1);
    }
};

template <>
struct Serializer<ublox_msgs::CfgPRT> {
    typedef boost::call_traits<ublox_msgs::CfgPRT> CallTraits;
    static void read(const uint8_t *data, uint32_t count,
                     typename CallTraits::reference m) {
        ublox::serialization::IStream stream(const_cast<uint8_t *>(data), count);
        stream.next(m.portID);
        stream.next(m.reserved0);
        stream.next(m.txReady);
        stream.next(m.mode);
        stream.next(m.baudRate);
        stream.next(m.inProtoMask);
        stream.next(m.outProtoMask);
        stream.next(m.flags);
        stream.next(m.reserved1);
    }

    static uint32_t serializedLength (typename CallTraits::param_type) {
        return sizeof(ublox_msgs::CfgPRT);
    }

    static void write(uint8_t *data, uint32_t size,
                      typename CallTraits::param_type m) {
        ublox::serialization::OStream stream(data, size);
        stream.next(m.portID);
        stream.next(m.reserved0);
        stream.next(m.txReady);
        stream.next(m.mode);
        stream.next(m.baudRate);
        stream.next(m.inProtoMask);
        stream.next(m.outProtoMask);
        stream.next(m.flags);
        stream.next(m.reserved1);
    }
};

template <>
struct Serializer<ublox_msgs::CfgRATE> {
    typedef boost::call_traits<ublox_msgs::CfgRATE> CallTraits;
    static void read(const uint8_t *data, uint32_t count,
                     typename CallTraits::reference m) {
        ublox::serialization::IStream stream(const_cast<uint8_t *>(data), count);
        stream.next(m.measRate);
        stream.next(m.navRate);
        stream.next(m.timeRef);
    }

    static uint32_t serializedLength (typename CallTraits::param_type) {
        return sizeof(ublox_msgs::CfgRATE);
    }

    static void write(uint8_t *data, uint32_t size,
                      typename CallTraits::param_type m) {
        ublox::serialization::OStream stream(data, size);
        stream.next(m.measRate);
        stream.next(m.navRate);
        stream.next(m.timeRef);
    }
};

template <>
struct Serializer<ublox_msgs::CfgSBAS> {
    typedef boost::call_traits<ublox_msgs::CfgSBAS> CallTraits;
    static void read(const uint8_t *data, uint32_t count,
                     typename CallTraits::reference m) {
        ublox::serialization::IStream stream(const_cast<uint8_t *>(data), count);
        stream.next(m.mode);
        stream.next(m.usage);
        stream.next(m.maxSBAS);
        stream.next(m.scanmode2);
        stream.next(m.scanmode1);
    }

    static uint32_t serializedLength (typename CallTraits::param_type) {
        return sizeof(ublox_msgs::CfgSBAS);
    }

    static void write(uint8_t *data, uint32_t size,
                      typename CallTraits::param_type m) {
        ublox::serialization::OStream stream(data, size);
        stream.next(m.mode);
        stream.next(m.usage);
        stream.next(m.maxSBAS);
        stream.next(m.scanmode2);
        stream.next(m.scanmode1);
    }
};

template <>
struct Serializer<ublox_msgs::CfgTMODE3> {
    typedef boost::call_traits<ublox_msgs::CfgTMODE3> CallTraits;
    static void read(const uint8_t *data, uint32_t count,
                     typename CallTraits::reference m) {
        ublox::serialization::IStream stream(const_cast<uint8_t *>(data), count);
        stream.next(m.version);
        stream.next(m.reserved1);
        stream.next(m.flags);
        stream.next(m.ecefXOrLat);
        stream.next(m.ecefYOrLon);
        stream.next(m.ecefZOrAlt);
        stream.next(m.ecefXOrLatHP);
        stream.next(m.ecefYOrLonHP);
        stream.next(m.ecefZOrAltHP);
        stream.next(m.reserved2);
        stream.next(m.fixedPosAcc);
        stream.next(m.svinMinDur);
        stream.next(m.svinAccLimit);
        stream.next(m.reserved3);
    }

    static uint32_t serializedLength (typename CallTraits::param_type) {
        return sizeof(ublox_msgs::CfgTMODE3);
    }

    static void write(uint8_t *data, uint32_t size,
                      typename CallTraits::param_type m) {
        ublox::serialization::OStream stream(data, size);
        stream.next(m.version);
        stream.next(m.reserved1);
        stream.next(m.flags);
        stream.next(m.ecefXOrLat);
        stream.next(m.ecefYOrLon);
        stream.next(m.ecefZOrAlt);
        stream.next(m.ecefXOrLatHP);
        stream.next(m.ecefYOrLonHP);
        stream.next(m.ecefZOrAltHP);
        stream.next(m.reserved2);
        stream.next(m.fixedPosAcc);
        stream.next(m.svinMinDur);
        stream.next(m.svinAccLimit);
        stream.next(m.reserved3);
    }
};

template <>
struct Serializer<ublox_msgs::CfgMSG> {
    typedef boost::call_traits<ublox_msgs::CfgMSG> CallTraits;
    static void read(const uint8_t *data, uint32_t count,
                     typename CallTraits::reference m) {
        ublox::serialization::IStream stream(const_cast<uint8_t *>(data), count);
        stream.next(m.msgClass);
        stream.next(m.msgID);
        stream.next(m.rate);
    }

    static uint32_t serializedLength (typename CallTraits::param_type) {
        return sizeof(ublox_msgs::CfgMSG);
    }

    static void write(uint8_t *data, uint32_t size,
                      typename CallTraits::param_type m) {
        ublox::serialization::OStream stream(data, size);
        stream.next(m.msgClass);
        stream.next(m.msgID);
        stream.next(m.rate);
    }
};

template <>
struct Serializer<ublox_msgs::CfgNAV5> {
    typedef boost::call_traits<ublox_msgs::CfgNAV5> CallTraits;
    static void read(const uint8_t *data, uint32_t count,
                     typename CallTraits::reference m) {
        ublox::serialization::IStream stream(const_cast<uint8_t *>(data), count);
        stream.next(m.mask);
        stream.next(m.dynModel);
        stream.next(m.fixMode);
        stream.next(m.fixedAlt);
        stream.next(m.fixedAltVar);
        stream.next(m.minElev);
        stream.next(m.drLimit);
        stream.next(m.pDop);
        stream.next(m.tDop);
        stream.next(m.pAcc);
        stream.next(m.tAcc);
        stream.next(m.staticHoldThresh);
        stream.next(m.dgnssTimeOut);
        stream.next(m.cnoThreshNumSvs);
        stream.next(m.cnoThresh);
        stream.next(m.reserved1);
        stream.next(m.staticHoldMaxDist);
        stream.next(m.utcStandard);
        stream.next(m.reserved2);
    }

    static uint32_t serializedLength (typename CallTraits::param_type) {
        return sizeof(ublox_msgs::CfgNAV5);
    }

    static void write(uint8_t *data, uint32_t size,
                      typename CallTraits::param_type m) {
        ublox::serialization::OStream stream(data, size);
        stream.next(m.mask);
        stream.next(m.dynModel);
        stream.next(m.fixMode);
        stream.next(m.fixedAlt);
        stream.next(m.fixedAltVar);
        stream.next(m.minElev);
        stream.next(m.drLimit);
        stream.next(m.pDop);
        stream.next(m.tDop);
        stream.next(m.pAcc);
        stream.next(m.tAcc);
        stream.next(m.staticHoldThresh);
        stream.next(m.dgnssTimeOut);
        stream.next(m.cnoThreshNumSvs);
        stream.next(m.cnoThresh);
        stream.next(m.reserved1);
        stream.next(m.staticHoldMaxDist);
        stream.next(m.utcStandard);
        stream.next(m.reserved2);
    }
};

template <>
struct Serializer<ublox_msgs::CfgNAVX5> {
    typedef boost::call_traits<ublox_msgs::CfgNAVX5> CallTraits;
    static void read(const uint8_t *data, uint32_t count,
                     typename CallTraits::reference m) {
        ublox::serialization::IStream stream(const_cast<uint8_t *>(data), count);
        stream.next(m.version);
        stream.next(m.mask1);
        stream.next(m.mask2);
        stream.next(m.reserved1);
        stream.next(m.minSVs);
        stream.next(m.maxSVs);
        stream.next(m.minCNO);
        stream.next(m.reserved2);
        stream.next(m.iniFix3D);
        stream.next(m.reserved3);
        stream.next(m.ackAiding);
        stream.next(m.wknRollover);
        stream.next(m.sigAttenCompMode);
        stream.next(m.reserved4);
        stream.next(m.usePPP);
        stream.next(m.aopCfg);
        stream.next(m.reserved5);
        stream.next(m.aopOrbMaxErr);
        stream.next(m.reserved6);
        stream.next(m.useAdr);
    }

    static uint32_t serializedLength (typename CallTraits::param_type) {
        return sizeof(ublox_msgs::CfgNAVX5);
    }

    static void write(uint8_t *data, uint32_t size,
                      typename CallTraits::param_type m) {
        ublox::serialization::OStream stream(data, size);
        stream.next(m.version);
        stream.next(m.mask1);
        stream.next(m.mask2);
        stream.next(m.reserved1);
        stream.next(m.minSVs);
        stream.next(m.maxSVs);
        stream.next(m.minCNO);
        stream.next(m.reserved2);
        stream.next(m.iniFix3D);
        stream.next(m.reserved3);
        stream.next(m.ackAiding);
        stream.next(m.wknRollover);
        stream.next(m.sigAttenCompMode);
        stream.next(m.reserved4);
        stream.next(m.usePPP);
        stream.next(m.aopCfg);
        stream.next(m.reserved5);
        stream.next(m.aopOrbMaxErr);
        stream.next(m.reserved6);
        stream.next(m.useAdr);
    }
};

template <>
struct Serializer<ublox_msgs::CfgDGNSS> {
    typedef boost::call_traits<ublox_msgs::CfgDGNSS> CallTraits;
    static void read(const uint8_t *data, uint32_t count,
                     typename CallTraits::reference m) {
        ublox::serialization::IStream stream(const_cast<uint8_t *>(data), count);
        stream.next(m.dgnssMode);
        stream.next(m.reserved0);
    }

    static uint32_t serializedLength (typename CallTraits::param_type) {
        return sizeof(ublox_msgs::CfgDGNSS);
    }

    static void write(uint8_t *data, uint32_t size,
                      typename CallTraits::param_type m) {
        ublox::serialization::OStream stream(data, size);
        stream.next(m.dgnssMode);
        stream.next(m.reserved0);
    }
};

template <>
struct Serializer<ublox_msgs::UpdSOS_Ack> {
    typedef boost::call_traits<ublox_msgs::UpdSOS_Ack> CallTraits;
    static void read(const uint8_t *data, uint32_t count,
                     typename CallTraits::reference m) {
        ublox::serialization::IStream stream(const_cast<uint8_t *>(data), count);
        stream.next(m.cmd);
        stream.next(m.reserved0);
        stream.next(m.response);
        stream.next(m.reserved1);
    }

    static uint32_t serializedLength (typename CallTraits::param_type) {
        return sizeof(ublox_msgs::UpdSOS_Ack);
    }

    static void write(uint8_t *data, uint32_t size,
                      typename CallTraits::param_type m) {
        ublox::serialization::OStream stream(data, size);
        stream.next(m.cmd);
        stream.next(m.reserved0);
        stream.next(m.response);
        stream.next(m.reserved1);
    }
};

template <>
struct Serializer<ublox_msgs::Ack> {
    typedef boost::call_traits<ublox_msgs::Ack> CallTraits;
    static void read(const uint8_t *data, uint32_t count,
                     typename CallTraits::reference m) {
        ublox::serialization::IStream stream(const_cast<uint8_t *>(data), count);
        stream.next(m.clsID);
        stream.next(m.msgID);
    }

    static uint32_t serializedLength (typename CallTraits::param_type) {
        return sizeof(ublox_msgs::Ack);
    }

    static void write(uint8_t *data, uint32_t size,
                      typename CallTraits::param_type m) {
        ublox::serialization::OStream stream(data, size);
        stream.next(m.clsID);
        stream.next(m.msgID);
    }
};

///
/// @brief Serializes the CfgGNSS message which has a repeated block.
///
template <>
struct Serializer<ublox_msgs::CfgGNSS > {
  typedef ublox_msgs::CfgGNSS Msg;
  typedef boost::call_traits<Msg> CallTraits;

  static void read(const uint8_t *data, uint32_t count, 
                   typename CallTraits::reference m) {
    ublox::serialization::IStream stream(const_cast<uint8_t *>(data), count);
    stream.next(m.msgVer);
    stream.next(m.numTrkChHw);
    stream.next(m.numTrkChUse);
    stream.next(m.numConfigBlocks);
    m.blocks.resize(m.numConfigBlocks);
    for(std::size_t i = 0; i < m.blocks.size(); ++i) 
      ublox::serialization::deserialize(stream, m.blocks[i]);
  }

  static uint32_t serializedLength (typename CallTraits::param_type m) {
    return 4 + 8 * m.numConfigBlocks;
  }

  static void write(uint8_t *data, uint32_t size, 
                    typename CallTraits::param_type m) {
    if(m.blocks.size() != m.numConfigBlocks) {
      //ROS_ERROR("CfgGNSS numConfigBlocks must equal blocks size");
    }
    ublox::serialization::OStream stream(data, size);
    stream.next(m.msgVer);
    stream.next(m.numTrkChHw);
    stream.next(m.numTrkChUse);
    stream.next(static_cast<uint8_t>(m.blocks.size()));
    for(std::size_t i = 0; i < m.blocks.size(); ++i) 
      ublox::serialization::serialize(stream, m.blocks[i]);
  }
};

///
/// @brief Serializes the CfgInf message which has a repeated block.
///
template <>
struct Serializer<ublox_msgs::CfgINF > {
  typedef boost::call_traits<ublox_msgs::CfgINF > 
      CallTraits;

  static void read(const uint8_t *data, uint32_t count,
                   typename CallTraits::reference m) {
    ublox::serialization::IStream stream(const_cast<uint8_t *>(data), count);
    std::size_t num_blocks = count / 10;
    m.blocks.resize(num_blocks);
    for(std::size_t i = 0; i < num_blocks; ++i) 
      ublox::serialization::deserialize(stream, m.blocks[i]);
  }

  static uint32_t serializedLength (typename CallTraits::param_type m) {
    return 10 * m.blocks.size();
  }

  static void write(uint8_t *data, uint32_t size, 
                    typename CallTraits::param_type m) {
    ublox::serialization::OStream stream(data, size);
    for(std::size_t i = 0; i < m.blocks.size(); ++i) 
      ublox::serialization::serialize(stream, m.blocks[i]);
  }
};

///
/// @brief Serializes the Inf message which has a dynamic length string.
///
template <>
struct Serializer<ublox_msgs::Inf > {
    typedef boost::call_traits<ublox_msgs::Inf > CallTraits;

    static void read(const uint8_t *data, uint32_t count,
                     typename CallTraits::reference m) {
        ublox::serialization::IStream stream(const_cast<uint8_t *>(data), count);
        m.str.resize(count);
        for (std::size_t i = 0; i < count; ++i)
            ublox::serialization::deserialize(stream, m.str[i]);
    }

    static uint32_t serializedLength (typename CallTraits::param_type m) {
        return m.str.size();
    }

    static void write(uint8_t *data, uint32_t size,
                      typename CallTraits::param_type m) {
        ublox::serialization::OStream stream(data, size);
        for(std::size_t i = 0; i < m.str.size(); ++i)
            ublox::serialization::serialize(stream, m.str[i]);
    }
};

///
/// @brief Serializes the MonVER message which has a repeated block.
///
template <>
struct Serializer<ublox_msgs::MonVER > {
  typedef ublox_msgs::MonVER Msg;
  typedef boost::call_traits<Msg> CallTraits;

  static void read(const uint8_t *data, uint32_t count, 
                   typename CallTraits::reference m) {
    ublox::serialization::IStream stream(const_cast<uint8_t *>(data), count);
    stream.next(m.swVersion);
    stream.next(m.hwVersion);

    m.extension.clear();
    int N = (count - 40) / 30;
    m.extension.reserve(N);
    ublox_msgs::MonVER_Extension ext;
    for (int i = 0; i < N; i++) {
      // Read each extension string
      ublox::serialization::deserialize(stream, ext);
      m.extension.push_back(ext);
    }
  }

  static uint32_t serializedLength(typename CallTraits::param_type m) {
    return 40 + (30 * m.extension.size());
  }

  static void write(uint8_t *data, uint32_t size, 
                    typename CallTraits::param_type m) {
    ublox::serialization::OStream stream(data, size);
    stream.next(m.swVersion);
    stream.next(m.hwVersion);
    for(std::size_t i = 0; i < m.extension.size(); ++i) 
      ublox::serialization::serialize(stream, m.extension[i]);
  }
};

///
/// @brief Serializes the NavDGPS message which has a repeated block.
///
template <>
struct Serializer<ublox_msgs::NavDGPS > {
  typedef ublox_msgs::NavDGPS Msg;
  typedef boost::call_traits<Msg> CallTraits;

  static void read(const uint8_t *data, uint32_t count, 
                   typename CallTraits::reference m) {
    ublox::serialization::IStream stream(const_cast<uint8_t *>(data), count);
    stream.next(m.iTOW);
    stream.next(m.age);
    stream.next(m.baseId);
    stream.next(m.baseHealth);
    stream.next(m.numCh);
    stream.next(m.status);
    stream.next(m.reserved1);
    m.sv.resize(m.numCh);
    for(std::size_t i = 0; i < m.sv.size(); ++i) 
      ublox::serialization::deserialize(stream, m.sv[i]);
  }

  static uint32_t serializedLength (typename CallTraits::param_type m) {
    return 16 + 12 * m.numCh;
  }

  static void write(uint8_t *data, uint32_t size, 
                    typename CallTraits::param_type m) {
    if(m.sv.size() != static_cast<unsigned  int>(m.numCh)) {
      //ROS_ERROR("NavDGPS numCh must equal sv size");
    }
    ublox::serialization::OStream stream(data, size);
    stream.next(m.iTOW);
    stream.next(m.age);
    stream.next(m.baseId);
    stream.next(m.baseHealth);
    stream.next(static_cast<uint8_t>(m.sv.size()));
    stream.next(m.status);
    stream.next(m.reserved1);
    for(std::size_t i = 0; i < m.sv.size(); ++i) 
      ublox::serialization::serialize(stream, m.sv[i]);
  }
};


///
/// @brief Serializes the NavSBAS message which has a repeated block.
///
template <>
struct Serializer<ublox_msgs::NavSBAS > {
  typedef ublox_msgs::NavSBAS Msg;
  typedef boost::call_traits<Msg> CallTraits;

  static void read(const uint8_t *data, uint32_t count, 
                   typename CallTraits::reference m) {
    ublox::serialization::IStream stream(const_cast<uint8_t *>(data), count);
    stream.next(m.iTOW);
    stream.next(m.geo);
    stream.next(m.mode);
    stream.next(m.sys);
    stream.next(m.service);
    stream.next(m.cnt);
    stream.next(m.reserved0);
    m.sv.resize(m.cnt);
    for(std::size_t i = 0; i < m.sv.size(); ++i) 
      ublox::serialization::deserialize(stream, m.sv[i]);
  }

  static uint32_t serializedLength (typename CallTraits::param_type m) {
    return 12 + 12 * m.cnt;
  }

  static void write(uint8_t *data, uint32_t size, 
                    typename CallTraits::param_type m) {
    if(m.sv.size() != m.cnt) {
      //ROS_ERROR("NavSBAS cnt must equal sv size");
    }
    ublox::serialization::OStream stream(data, size);
    stream.next(m.iTOW);
    stream.next(m.geo);
    stream.next(m.mode);
    stream.next(m.sys);
    stream.next(m.service);
    stream.next(static_cast<uint8_t>(m.sv.size()));
    stream.next(m.reserved0);
    for(std::size_t i = 0; i < m.sv.size(); ++i) 
      ublox::serialization::serialize(stream, m.sv[i]);
  }
};

///
/// @brief Serializes the NavSAT message which has a repeated block.
///
template <>
struct Serializer<ublox_msgs::NavSAT > {
  typedef ublox_msgs::NavSAT Msg;
  typedef boost::call_traits<Msg> CallTraits;

  static void read(const uint8_t *data, uint32_t count, 
                   typename CallTraits::reference m) {
    ublox::serialization::IStream stream(const_cast<uint8_t *>(data), count);
    stream.next(m.iTOW);
    stream.next(m.version);
    stream.next(m.numSvs);
    stream.next(m.reserved0);
    m.sv.resize(m.numSvs);
    for(std::size_t i = 0; i < m.sv.size(); ++i) 
      ublox::serialization::deserialize(stream, m.sv[i]);
  }

  static uint32_t serializedLength (typename CallTraits::param_type m) {
    return 8 + 12 * m.numSvs;
  }

  static void write(uint8_t *data, uint32_t size, 
                    typename CallTraits::param_type m) {
    if(m.sv.size() != m.numSvs) {
      //ROS_ERROR("NavSAT numSvs must equal sv size");
    }
    ublox::serialization::OStream stream(data, size);
    stream.next(m.iTOW);
    stream.next(m.version);
    stream.next(static_cast<uint8_t>(m.sv.size()));
    stream.next(m.reserved0);
    for(std::size_t i = 0; i < m.sv.size(); ++i) 
      ublox::serialization::serialize(stream, m.sv[i]);
  }
};

///
/// @brief Serializes the NavDGPS message which has a repeated block.
///
template <>
struct Serializer<ublox_msgs::NavSVINFO > {
  typedef ublox_msgs::NavSVINFO Msg;
  typedef boost::call_traits<Msg> CallTraits;

  static void read(const uint8_t *data, uint32_t count, 
                   typename CallTraits::reference m) {
    ublox::serialization::IStream stream(const_cast<uint8_t *>(data), count);
    stream.next(m.iTOW);
    stream.next(m.numCh);
    stream.next(m.globalFlags);
    stream.next(m.reserved2);
    m.sv.resize(m.numCh);
    for(std::size_t i = 0; i < m.sv.size(); ++i) 
      ublox::serialization::deserialize(stream, m.sv[i]);
  }

  static uint32_t serializedLength (typename CallTraits::param_type m) {
    return 8 + 12 * m.numCh;
  }

  static void write(uint8_t *data, uint32_t size, 
                    typename CallTraits::param_type m) {
    if(m.sv.size() != m.numCh) {
      //ROS_ERROR("NavSVINFO numCh must equal sv size");
    }
    ublox::serialization::OStream stream(data, size);
    stream.next(m.iTOW);
    stream.next(static_cast<uint8_t>(m.sv.size()));
    stream.next(m.globalFlags);
    stream.next(m.reserved2);
    for(std::size_t i = 0; i < m.sv.size(); ++i) 
      ublox::serialization::serialize(stream, m.sv[i]);
  }
};

///
/// @brief Serializes the RxmRAW message which has a repeated block.
///
template <>
struct Serializer<ublox_msgs::RxmRAW > {
  typedef ublox_msgs::RxmRAW Msg;
  typedef boost::call_traits<Msg> CallTraits;

  static void read(const uint8_t *data, uint32_t count, 
                   typename CallTraits::reference m) {
    ublox::serialization::IStream stream(const_cast<uint8_t *>(data), count);
    stream.next(m.rcvTOW);
    stream.next(m.week);
    stream.next(m.numSV);
    stream.next(m.reserved1);
    m.sv.resize(m.numSV);
    for(std::size_t i = 0; i < m.sv.size(); ++i) 
      ublox::serialization::deserialize(stream, m.sv[i]);
  }

  static uint32_t serializedLength (typename CallTraits::param_type m) {
    return 8 + 24 * m.numSV;
  }

  static void write(uint8_t *data, uint32_t size, 
                    typename CallTraits::param_type m) {
    if(m.sv.size() != m.numSV) {
      //ROS_ERROR("RxmRAW numSV must equal sv size");
    }
    ublox::serialization::OStream stream(data, size);
    stream.next(m.rcvTOW);
    stream.next(m.week);
    stream.next(static_cast<uint8_t>(m.sv.size()));
    stream.next(m.reserved1);
    for(std::size_t i = 0; i < m.sv.size(); ++i) 
      ublox::serialization::serialize(stream, m.sv[i]);
  }
};

///
/// @brief Serializes the RxmRAWX message which has a repeated block.
///
template <>
struct Serializer<ublox_msgs::RxmRAWX > {
  typedef ublox_msgs::RxmRAWX Msg;
  typedef boost::call_traits<Msg> CallTraits;

  static void read(const uint8_t *data, uint32_t count, 
                   typename CallTraits::reference m) {
    ublox::serialization::IStream stream(const_cast<uint8_t *>(data), count);
    stream.next(m.rcvTOW);
    stream.next(m.week);
    stream.next(m.leapS);
    stream.next(m.numMeas);
    stream.next(m.recStat);
    stream.next(m.version);
    stream.next(m.reserved1);
    m.meas.resize(m.numMeas);
    for(std::size_t i = 0; i < m.meas.size(); ++i) 
      ublox::serialization::deserialize(stream, m.meas[i]);
  }

  static uint32_t serializedLength (typename CallTraits::param_type m) {
    return 16 + 32 * m.numMeas;
  }

  static void write(uint8_t *data, uint32_t size, 
                    typename CallTraits::param_type m) {
    if(m.meas.size() != m.numMeas) {
      //ROS_ERROR("RxmRAWX numMeas must equal meas size");
    }
    ublox::serialization::OStream stream(data, size);
    stream.next(m.rcvTOW);
    stream.next(m.week);
    stream.next(m.leapS);
    stream.next(static_cast<uint8_t >(m.meas.size()));
    stream.next(m.recStat);
    stream.next(m.version);
    stream.next(m.reserved1);
    for(std::size_t i = 0; i < m.meas.size(); ++i) 
      ublox::serialization::serialize(stream, m.meas[i]);
  }
};

///
/// @brief Serializes the RxmSFRBX message which has a repeated block.
///
template <>
struct Serializer<ublox_msgs::RxmSFRBX > {
  typedef ublox_msgs::RxmSFRBX Msg;
  typedef boost::call_traits<Msg> CallTraits;

  static void read(const uint8_t *data, uint32_t count, 
                   typename CallTraits::reference m) {
    ublox::serialization::IStream stream(const_cast<uint8_t *>(data), count);
    stream.next(m.gnssId);
    stream.next(m.svId);
    stream.next(m.reserved0);
    stream.next(m.freqId);
    stream.next(m.numWords);
    stream.next(m.chn);
    stream.next(m.version);
    stream.next(m.reserved1);
    m.dwrd.resize(m.numWords);
    for(std::size_t i = 0; i < m.dwrd.size(); ++i) {
        stream.next(m.dwrd[i]);
    }
  }

  static uint32_t serializedLength (typename CallTraits::param_type m) {
    return 8 + 4 * m.numWords;
  }

  static void write(uint8_t *data, uint32_t size, 
                    typename CallTraits::param_type m) {
    if(m.dwrd.size() != m.numWords) {
      //ROS_ERROR("RxmSFRBX numWords must equal dwrd size");
    }
    ublox::serialization::OStream stream(data, size);
    stream.next(m.gnssId);
    stream.next(m.svId);
    stream.next(m.reserved0);
    stream.next(m.freqId);
    stream.next(static_cast<uint8_t >(m.dwrd.size()));
    stream.next(m.chn);
    stream.next(m.version);
    stream.next(m.reserved1);
    for(std::size_t i = 0; i < m.dwrd.size(); ++i)  {
        stream.next(m.dwrd[i]);
    }
  }
};

///
/// @brief Serializes the RxmSVSI message which has a repeated block.
///
template <>
struct Serializer<ublox_msgs::RxmSVSI > {
  typedef ublox_msgs::RxmSVSI Msg;
  typedef boost::call_traits<Msg> CallTraits;

  static void read(const uint8_t *data, uint32_t count, 
                   typename CallTraits::reference m) {
    ublox::serialization::IStream stream(const_cast<uint8_t *>(data), count);
    stream.next(m.iTOW);
    stream.next(m.week);
    stream.next(m.numVis);
    stream.next(m.numSV);
    m.sv.resize(m.numSV);
    for(std::size_t i = 0; i < m.sv.size(); ++i) 
      ublox::serialization::deserialize(stream, m.sv[i]);
  }

  static uint32_t serializedLength (typename CallTraits::param_type m) {
    return 8 + 6 * m.numSV;
  }

  static void write(uint8_t *data, uint32_t size, 
                    typename CallTraits::param_type m) {
    if(m.sv.size() != m.numSV) {
      //ROS_ERROR("RxmSVSI numSV must equal sv size");
    }
    ublox::serialization::OStream stream(data, size);
    stream.next(m.iTOW);
    stream.next(m.week);
    stream.next(m.numVis);
    stream.next(static_cast<uint8_t>(m.sv.size()));
    for(std::size_t i = 0; i < m.sv.size(); ++i) 
      ublox::serialization::serialize(stream, m.sv[i]);
  }
};

///
/// @brief Serializes the RxmALM message which has a repeated block.
///
template <>
struct Serializer<ublox_msgs::RxmALM > {
  typedef ublox_msgs::RxmALM Msg;
  typedef boost::call_traits<Msg> CallTraits;

  static void read(const uint8_t *data, uint32_t count, 
                   typename CallTraits::reference m) {
    ublox::serialization::IStream stream(const_cast<uint8_t *>(data), count);
    stream.next(m.svid);
    stream.next(m.week);

    m.dwrd.clear();
    if(count == 40) {
      uint32_t temp;
      m.dwrd.resize(8);
      for(std::size_t i = 0; i < 8; ++i) {
        stream.next(temp);
        m.dwrd.push_back(temp);
      }
    }
  }

  static uint32_t serializedLength (typename CallTraits::param_type m) {
    return 8 + (4 * m.dwrd.size());
  }

  static void write(uint8_t *data, uint32_t size, 
                    typename CallTraits::param_type m) {
    ublox::serialization::OStream stream(data, size);
    stream.next(m.svid);
    stream.next(m.week);
    for(std::size_t i = 0; i < m.dwrd.size(); ++i) 
      ublox::serialization::serialize(stream, m.dwrd[i]);
  }
};

///
/// @brief Serializes the RxmEPH message which has a repeated block.
///
template <>
struct Serializer<ublox_msgs::RxmEPH >
{
  typedef ublox_msgs::RxmEPH Msg;
  typedef boost::call_traits<Msg> CallTraits;

  static void read(const uint8_t *data, uint32_t count, 
                   typename CallTraits::reference m) {
    ublox::serialization::IStream stream(const_cast<uint8_t *>(data), count);
    stream.next(m.svid);
    stream.next(m.how);
    m.sf1d.clear();
    m.sf2d.clear();
    m.sf3d.clear();

    if (count == 104) {
      uint32_t temp1;
      uint32_t temp2;
      uint32_t temp3;

      m.sf1d.resize(8);
      for(std::size_t i = 0; i < 8; ++i) {
        stream.next(temp1);
        m.sf1d.push_back(temp1);
      }
      m.sf2d.resize(8);
      for(std::size_t i = 0; i < 8; ++i) {
        stream.next(temp2);
        m.sf2d.push_back(temp2);
      }
      m.sf3d.resize(8);
      for(std::size_t i = 0; i < 8; ++i) {
        stream.next(temp3);
        m.sf3d.push_back(temp3);
      }
    }
  }

  static uint32_t serializedLength (typename CallTraits::param_type m) {
    return 8 + (4 * m.sf1d.size()) + (4 * m.sf2d.size()) + (4 * m.sf3d.size());
  }

  static void write(uint8_t *data, uint32_t size, 
                    typename CallTraits::param_type m) {
    ublox::serialization::OStream stream(data, size);
    stream.next(m.svid);
    stream.next(m.how);
    for(std::size_t i = 0; i < m.sf1d.size(); ++i) 
      ublox::serialization::serialize(stream, m.sf1d[i]);
    for(std::size_t i = 0; i < m.sf2d.size(); ++i) 
      ublox::serialization::serialize(stream, m.sf2d[i]);
    for(std::size_t i = 0; i < m.sf3d.size(); ++i) 
      ublox::serialization::serialize(stream, m.sf3d[i]);
  }
};

///
/// @brief Serializes the AidALM message which has a repeated block.
///
template <>
struct Serializer<ublox_msgs::AidALM > {
  typedef ublox_msgs::AidALM Msg;
  typedef boost::call_traits<Msg> CallTraits;

  static void read(const uint8_t *data, uint32_t count, 
                   typename CallTraits::reference m) {
    ublox::serialization::IStream stream(const_cast<uint8_t *>(data), count);
    stream.next(m.svid);
    stream.next(m.week);

    m.dwrd.clear();
    if (count == 40) {
      uint32_t temp;
      m.dwrd.resize(8);
      for(std::size_t i = 0; i < 8; ++i) {
        stream.next(temp);
        m.dwrd.push_back(temp);
      }
    } 
  }

  static uint32_t serializedLength (typename CallTraits::param_type m) {
    return 8 + (4 * m.dwrd.size());
  }

  static void write(uint8_t *data, uint32_t size, 
                    typename CallTraits::param_type m) {
    ublox::serialization::OStream stream(data, size);
    stream.next(m.svid);
    stream.next(m.week);
    for(std::size_t i = 0; i < m.dwrd.size(); ++i) 
      ublox::serialization::serialize(stream, m.dwrd[i]);
  }
};

///
/// @brief Serializes the AidEPH message which has a repeated block.
///
template <>
struct Serializer<ublox_msgs::AidEPH >
{
  typedef ublox_msgs::AidEPH Msg;
  typedef boost::call_traits<Msg> CallTraits;

  static void read(const uint8_t *data, uint32_t count, 
                   typename CallTraits::reference m) {
    ublox::serialization::IStream stream(const_cast<uint8_t *>(data), count);
    stream.next(m.svid);
    stream.next(m.how);
    m.sf1d.clear();
    m.sf2d.clear();
    m.sf3d.clear();

    if (count == 104) {
      uint32_t temp1;
      uint32_t temp2;
      uint32_t temp3;

      m.sf1d.resize(8);
      for(std::size_t i = 0; i < 8; ++i) {
        stream.next(temp1);
        m.sf1d.push_back(temp1);
      }
      m.sf2d.resize(8);
      for(std::size_t i = 0; i < 8; ++i) {
        stream.next(temp2);
        m.sf2d.push_back(temp2);
      }
      m.sf3d.resize(8);
      for(std::size_t i = 0; i < 8; ++i) {
        stream.next(temp3);
        m.sf3d.push_back(temp3);
      }
    }
  }

  static uint32_t serializedLength (typename CallTraits::param_type m) {
    return 8 + (4 * m.sf1d.size()) + (4 * m.sf2d.size()) + (4 * m.sf3d.size());
  }

  static void write(uint8_t *data, uint32_t size, 
                    typename CallTraits::param_type m) {
    ublox::serialization::OStream stream(data, size);
    stream.next(m.svid);
    stream.next(m.how);
    for(std::size_t i = 0; i < m.sf1d.size(); ++i) 
      ublox::serialization::serialize(stream, m.sf1d[i]);
    for(std::size_t i = 0; i < m.sf2d.size(); ++i) 
      ublox::serialization::serialize(stream, m.sf2d[i]);
    for(std::size_t i = 0; i < m.sf3d.size(); ++i) 
      ublox::serialization::serialize(stream, m.sf3d[i]);
  }
};

///
/// @brief Serializes the EsfMEAS message which has a repeated block and an
/// optional block.
///
template <>
struct Serializer<ublox_msgs::EsfMEAS > {
  typedef boost::call_traits<ublox_msgs::EsfMEAS > 
      CallTraits;

  static void read(const uint8_t *data, uint32_t count, 
                   typename CallTraits::reference m) {
    ublox::serialization::IStream stream(const_cast<uint8_t *>(data), count);
    stream.next(m.timeTag);
    stream.next(m.flags);
    stream.next(m.id);

    bool calib_valid = m.flags & m.FLAGS_CALIB_T_TAG_VALID;
    unsigned int data_size = (count - (calib_valid ? 12 : 8)) / 4;
    // Repeating block
    m.data.resize(data_size);
    for(std::size_t i = 0; i < data_size; ++i)  {
        stream.next(m.data[i]);
    }
    // Optional block
    if(calib_valid) {
      m.calibTtag.resize(1);
      stream.next(m.calibTtag[0]);
    }
  }

  static uint32_t serializedLength (typename CallTraits::param_type m) {
    return 4 + 8 * m.data.size() + 4 * m.calibTtag.size();
  }

  static void write(uint8_t *data, uint32_t size, 
                    typename CallTraits::param_type m) {
    ublox::serialization::OStream stream(data, size);
    stream.next(m.timeTag);
    stream.next(m.flags);
    stream.next(m.id);
    for(std::size_t i = 0; i < m.data.size(); ++i) 
      ublox::serialization::serialize(stream, m.data[i]);
    for(std::size_t i = 0; i < m.calibTtag.size(); ++i) 
      ublox::serialization::serialize(stream, m.calibTtag[i]);
  }
};

///
/// @brief Serializes the EsfRAW message which has a repeated block.
///
template <>
struct Serializer<ublox_msgs::EsfRAW > {
  typedef boost::call_traits<ublox_msgs::EsfRAW > 
      CallTraits;

  static void read(const uint8_t *data, uint32_t count, 
                   typename CallTraits::reference m) {
    ublox::serialization::IStream stream(const_cast<uint8_t *>(data), count);
    stream.next(m.reserved0);
    m.blocks.clear();
    unsigned int num_blocks = (count - 4) / 8;
    m.blocks.resize(num_blocks);
    for(std::size_t i = 0; i < num_blocks; ++i) 
      ublox::serialization::deserialize(stream, m.blocks[i]);
  }


  static uint32_t serializedLength (typename CallTraits::param_type m) {
    return 4 + 8 * m.blocks.size();
  }

  static void write(uint8_t *data, uint32_t size, 
                    typename CallTraits::param_type m) {
    ublox::serialization::OStream stream(data, size);
    stream.next(m.reserved0);
    for(std::size_t i = 0; i < m.blocks.size(); ++i) 
      ublox::serialization::serialize(stream, m.blocks[i]);
  }
};

///
/// @brief Serializes the EsfSTATUS message which has a repeated block.
///
template <>
struct Serializer<ublox_msgs::EsfSTATUS > {
  typedef ublox_msgs::EsfSTATUS Msg;
  typedef boost::call_traits<Msg> CallTraits;

  static void read(const uint8_t *data, uint32_t count, 
                   typename CallTraits::reference m) {
    ublox::serialization::IStream stream(const_cast<uint8_t *>(data), count);
    stream.next(m.iTOW);
    stream.next(m.version);
    stream.next(m.fusionMode);
    stream.next(m.reserved2);
    stream.next(m.numSens);
    m.sens.resize(m.numSens);
    for(std::size_t i = 0; i < m.sens.size(); ++i) 
      ublox::serialization::deserialize(stream, m.sens[i]);
  }

  static uint32_t serializedLength (typename CallTraits::param_type m) {
    return 16 + 4 * m.numSens;
  }

  static void write(uint8_t *data, uint32_t size, 
                    typename CallTraits::param_type m) {
    if(m.sens.size() != m.numSens) {
      //ROS_ERROR("Writing EsfSTATUS message: numSens must equal size of sens");
    }
    ublox::serialization::OStream stream(data, size);
    stream.next(m.iTOW);
    stream.next(m.version);
    stream.next(m.fusionMode);
    stream.next(m.reserved2);
    stream.next(static_cast<uint8_t>(m.sens.size()));
    for(std::size_t i = 0; i < m.sens.size(); ++i) 
      ublox::serialization::serialize(stream, m.sens[i]);
  }
};

template <>
struct Serializer<ublox_msgs::NavRELPOSNED9 > {
    typedef ublox_msgs::NavRELPOSNED9 Msg;
    typedef boost::call_traits<Msg> CallTraits;

    static void read(const uint8_t *data, uint32_t count,
                     typename CallTraits::reference m) {
        ublox::serialization::IStream stream(const_cast<uint8_t *>(data), count);
        stream.next(m.version);
        stream.next(m.reserved1);
        stream.next(m.refStationId);
        stream.next(m.iTow);
        stream.next(m.relPosN);
        stream.next(m.relPosE);
        stream.next(m.relPosD);
        stream.next(m.relPosLength);
        stream.next(m.relPosHeading);
        stream.next(m.reserved2);
        stream.next(m.relPosHPN);
        stream.next(m.relPosHPE);
        stream.next(m.relPosHPD);
        stream.next(m.relPosHPLength);
        stream.next(m.accN);
        stream.next(m.accE);
        stream.next(m.accD);
        stream.next(m.accLength);
        stream.next(m.accHeading);
        stream.next(m.reserved3);
        stream.next(m.flags);
    }

    static uint32_t serializedLength (typename CallTraits::param_type) {
        return sizeof(ublox_msgs::NavRELPOSNED9);
    }

    static void write(uint8_t *data, uint32_t size,
                      typename CallTraits::param_type m) {
        ublox::serialization::OStream stream(data, size);
        stream.next(m.version);
        stream.next(m.reserved1);
        stream.next(m.refStationId);
        stream.next(m.iTow);
        stream.next(m.relPosN);
        stream.next(m.relPosE);
        stream.next(m.relPosD);
        stream.next(m.relPosLength);
        stream.next(m.relPosHeading);
        stream.next(m.reserved2);
        stream.next(m.relPosHPN);
        stream.next(m.relPosHPE);
        stream.next(m.relPosHPD);
        stream.next(m.relPosHPLength);
        stream.next(m.accN);
        stream.next(m.accE);
        stream.next(m.accD);
        stream.next(m.accLength);
        stream.next(m.accHeading);
        stream.next(m.reserved3);
        stream.next(m.flags);
    }
};

template <>
struct Serializer<ublox_msgs::MonVER_Extension > {
    typedef ublox_msgs::MonVER_Extension Msg;
    typedef boost::call_traits<Msg> CallTraits;

    static void read(const uint8_t *data, uint32_t count,
                     typename CallTraits::reference m) {
        ublox::serialization::IStream stream(const_cast<uint8_t *>(data), count);
        stream.next(m.field);
    }

    static uint32_t serializedLength (typename CallTraits::param_type) {
        return sizeof(ublox_msgs::MonVER_Extension);
    }

    static void write(uint8_t *data, uint32_t size,
                      typename CallTraits::param_type m) {
        ublox::serialization::OStream stream(data, size);
        stream.next(m.field);
    }
};


template <>
struct Serializer<ublox_msgs::NavSVIN > {
    typedef ublox_msgs::NavSVIN Msg;
    typedef boost::call_traits<Msg> CallTraits;

    template<class T, class MSG>
    static void doNext(T& stream, MSG& m) {
        stream.next(m.version);
        stream.next(m.reserved0);
        stream.next(m.iTOW);
        stream.next(m.dur);
        stream.next(m.meanX);
        stream.next(m.meanY);
        stream.next(m.meanZ);
        stream.next(m.meanXHP);
        stream.next(m.meanYHP);
        stream.next(m.meanZHP);
        stream.next(m.reserved1);
        stream.next(m.meanAcc);
        stream.next(m.obs);
        stream.next(m.valid);
        stream.next(m.active);
        stream.next(m.reserved3);
    }

    static void read(const uint8_t *data, uint32_t count,
                     typename CallTraits::reference m) {
        ublox::serialization::IStream stream(const_cast<uint8_t *>(data), count);
        doNext(stream, m);
    }

    static uint32_t serializedLength (typename CallTraits::param_type) {
        return sizeof(ublox_msgs::NavSVIN);
    }

    static void write(uint8_t *data, uint32_t size,
                      typename CallTraits::param_type m) {
        ublox::serialization::OStream stream(data, size);
        doNext(stream, m);
    }
};

template <>
struct Serializer<ublox_msgs::NavPVT > {
    typedef ublox_msgs::NavPVT Msg;
    typedef boost::call_traits<Msg> CallTraits;

    template<class T, class M>
    static void doNext(T& stream, M& m) {
        stream.next(m.iTOW);
        stream.next(m.year);
        stream.next(m.month);
        stream.next(m.day);
        stream.next(m.hour);
        stream.next(m.min);
        stream.next(m.sec);
        stream.next(m.valid);
        stream.next(m.tAcc);
        stream.next(m.nano);
        stream.next(m.fixType);
        stream.next(m.flags);
        stream.next(m.flags2);
        stream.next(m.numSV);
        stream.next(m.lon);
        stream.next(m.lat);
        stream.next(m.height);
        stream.next(m.hMSL);
        stream.next(m.hAcc);
        stream.next(m.vAcc);
        stream.next(m.velN);
        stream.next(m.velE);
        stream.next(m.velD);
        stream.next(m.gSpeed);
        stream.next(m.heading);
        stream.next(m.sAcc);
        stream.next(m.headAcc);
        stream.next(m.pDOP);
        stream.next(m.reserved1);
        stream.next(m.headVeh);
        stream.next(m.magDec);
        stream.next(m.magAcc);
    }

    static void read(const uint8_t *data, uint32_t count,
                     typename CallTraits::reference m) {
        ublox::serialization::IStream stream(const_cast<uint8_t *>(data), count);
        doNext(stream, m);
    }

    static uint32_t serializedLength (typename CallTraits::param_type) {
        return sizeof(ublox_msgs::NavPVT);
    }

    static void write(uint8_t *data, uint32_t size,
                      typename CallTraits::param_type m) {
        ublox::serialization::OStream stream(data, size);
        doNext(stream, m);
    }
};


template <>
struct Serializer<ublox_msgs::CfgCFG > {
    typedef ublox_msgs::CfgCFG Msg;
    typedef boost::call_traits<Msg> CallTraits;

    template<class T, class M>
    static void doNext(T& stream, M& m) {
        stream.next(m.clearMask);
        stream.next(m.saveMask);
        stream.next(m.loadMask);
        stream.next(m.deviceMask);
    }

    static void read(const uint8_t *data, uint32_t count,
                     typename CallTraits::reference m) {
        ublox::serialization::IStream stream(const_cast<uint8_t *>(data), count);
        doNext(stream, m);
    }

    static uint32_t serializedLength (typename CallTraits::param_type) {
        return sizeof(ublox_msgs::CfgCFG);
    }

    static void write(uint8_t *data, uint32_t size,
                      typename CallTraits::param_type m) {
        ublox::serialization::OStream stream(data, size);
        doNext(stream, m);
    }
};

template <>
struct Serializer<ublox_msgs::NavPOSLLH> {
    typedef ublox_msgs::NavPOSLLH Msg;
    typedef boost::call_traits<Msg> CallTraits;

    static void read(const uint8_t *data, uint32_t count,
                     typename CallTraits::reference m) {
        ublox::serialization::IStream stream(const_cast<uint8_t *>(data), count);
        stream.next(m.iTOW);
        stream.next(m.lon);
        stream.next(m.lat);
        stream.next(m.height);
        stream.next(m.hMSL);
        stream.next(m.hAcc);
        stream.next(m.vAcc);
    }

    static uint32_t serializedLength (typename CallTraits::param_type) {
        return sizeof(ublox_msgs::NavPOSLLH);
    }

    static void write(uint8_t *data, uint32_t size,
                      typename CallTraits::param_type m) {
        ublox::serialization::OStream stream(data, size);
        stream.next(m.iTOW);
        stream.next(m.lon);
        stream.next(m.lat);
        stream.next(m.height);
        stream.next(m.hMSL);
        stream.next(m.hAcc);
        stream.next(m.vAcc);
    }
};

} // namespace ublox

#endif // UBLOX_SERIALIZATION_UBLOX_MSGS_H

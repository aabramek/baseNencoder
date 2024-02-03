#include "base64.h"

#include <array>
#include <QtLogging>

QByteArray Base64::encode(const QByteArray &data)
{
    size_t length = data.length();
    QByteArray result;
    result.reserve((length + 2) * 4 / 3 / 3);
    size_t i = 0;
    size_t octetsLeft = length;

    while (octetsLeft >= 3) {
        result.push_back(alphabet.at(data[i] >> 2));
        result.push_back(alphabet.at(((data[i] << 4) & 0x3f) | (data[i + 1] >> 4)));
        result.push_back(alphabet.at(((data[i + 1] << 2) & 0x3f) | (data[i + 2] >> 6)));
        result.push_back(alphabet.at(data[i + 2] & 0x3f));
        i += 3;
        octetsLeft = length - i;
    }

    if (octetsLeft == 2) {
        result.push_back(alphabet.at(data[i] >> 2));
        result.push_back(alphabet.at(((data[i] << 4) & 0x3f) | (data[i + 1] >> 4)));
        result.push_back(alphabet.at(((data[i + 1] << 2) & 0x3f)));
        result.push_back('=');
    }
    else if (octetsLeft == 1) {
        result.push_back(alphabet.at(data[i] >> 2));
        result.push_back(alphabet.at((data[i] << 4) & 0x3f));
        result.push_back('=');
        result.push_back('=');
    }

    return result;
}

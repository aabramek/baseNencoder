#include "baseN.h"

#include <array>
#include <QString>
#include <QDebug>

QByteArray BaseNEncoder::encode64(const QByteArray &data)
{
    size_t length = data.length();

    QByteArray result;
    result.reserve((length + 2) / 3 * 4);

    size_t i = 0;
    size_t octetsLeft = length;

    std::array<size_t, 4> indices;

    const unsigned char *rawData = reinterpret_cast<const unsigned char*>(data.constData());

    while (octetsLeft >= 3) {
        indices[0] = rawData[i] >> 2;
        indices[1] = ((rawData[i] << 4) & 0x3f) | (rawData[i + 1] >> 4);
        indices[2] = ((rawData[i + 1] << 2) & 0x3f) | (rawData[i + 2] >> 6);
        indices[3] = rawData[i + 2] & 0x3f;

        std::for_each(indices.begin(), indices.end(), [&result](size_t i){
            result.push_back(base64alphabet[i]);
        });

        i += 3;
        octetsLeft -= 3;
    }

    if (octetsLeft == 0) {
        return result;
    }

    indices.fill(64);

    switch (octetsLeft) {
    case 2:
        indices[0] = rawData[i] >> 2;
        indices[1] = ((rawData[i] << 4) & 0x3f) | (rawData[i + 1] >> 4);
        indices[2] = (rawData[i + 1] << 2) & 0x3f;
        break;

    case 1:
        indices[0] = rawData[i] >> 2;
        indices[1] = (rawData[i] << 4) & 0x3f;
        break;
    }

    std::for_each(indices.begin(), indices.end(), [&result](size_t i){
        result.push_back(base64alphabet[i]);
    });

    return result;
}

QByteArray BaseNEncoder::encode32(const QByteArray &data)
{
    size_t length = data.length();

    QByteArray result;
    result.reserve((length + 4) / 5 * 8);

    size_t i = 0;
    size_t octetsLeft = length;

    std::array<size_t, 8> indices;

    const unsigned char *rawData = reinterpret_cast<const unsigned char*>(data.constData());

    while (octetsLeft >= 5) {
        indices[0] = rawData[i] >> 3;
        indices[1] = ((rawData[i] << 2) & 0x1f) | (rawData[i + 1] >> 6);
        indices[2] = (rawData[i + 1] >> 1) & 0x1f;
        indices[3] = ((rawData[i + 1] << 4) & 0x1f) | (rawData[i + 2] >> 4);
        indices[4] = ((rawData[i + 2] << 1) & 0x1f) | (rawData[i + 3] >> 7);
        indices[5] = (rawData[i + 3] >> 2) & 0x1f;
        indices[6] = ((rawData[i + 3] << 3) & 0x1f) | (rawData[i + 4] >> 5);
        indices[7] = rawData[i + 4] & 0x1f;

        std::for_each(indices.begin(), indices.end(), [&result](size_t i){
            result.push_back(base32alphabet.at(i));
        });

        i += 5;
        octetsLeft -= 5;
    }

    if (octetsLeft == 0) {
        return result;
    }

    indices.fill(32);

    switch (octetsLeft) {
    case 4:
        indices[0] = rawData[i] >> 3;
        indices[1] = ((rawData[i] << 2) & 0x1f) | (rawData[i + 1] >> 6);
        indices[2] = (rawData[i + 1] >> 1) & 0x1f;
        indices[3] = ((rawData[i + 1] << 4) & 0x1f) | (rawData[i + 2] >> 4);
        indices[4] = ((rawData[i + 2] << 1) & 0x1f) | (rawData[i + 3] >> 7);
        indices[5] = (rawData[i + 3] >> 2) & 0x1f;
        indices[6] = (rawData[i + 3] << 3) & 0x1f;
        break;
    case 3:
        indices[0] = rawData[i] >> 3;
        indices[1] = ((rawData[i] << 2) & 0x1f) | (rawData[i + 1] >> 6);
        indices[2] = (rawData[i + 1] >> 1) & 0x1f;
        indices[3] = ((rawData[i + 1] << 4) & 0x1f) | (rawData[i + 2] >> 4);
        indices[4] = (rawData[i + 2] << 1) & 0x1f;
        break;
    case 2:
        indices[0] = rawData[i] >> 3;
        indices[1] = ((rawData[i] << 2) & 0x1f) | (rawData[i + 1] >> 6);
        indices[2] = (rawData[i + 1] >> 1) & 0x1f;
        indices[3] = (rawData[i + 1] << 4) & 0x1f;
        break;
    case 1:
        indices[0] = rawData[i] >> 3;
        indices[1] = (rawData[i] << 2) & 0x1f;
        break;
    }

    std::for_each(indices.begin(), indices.end(), [&result](size_t i){
        result.push_back(base32alphabet.at(i));
    });

    return result;
}

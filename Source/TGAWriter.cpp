#include "TGAWriter.h"

#include <cstdio>
#include <cstring>

namespace Geode
{
    bool WriteTGA(const std::string& Name, uint16_t Width, uint16_t Height, const void* Data)
    {
        static constexpr size_t BytesPerPixel = 4;

        struct [[gnu::packed]] TGAHeader
        {
            uint8_t IDLength;
            uint8_t ColorMap;
            uint8_t ImageType;
            uint8_t Unused[5];
            uint16_t XOrigin;
            uint16_t YOrigin;
            uint16_t Width;
            uint16_t Height;
            uint8_t PixelDepth;
            uint8_t Descriptor;
        };

        struct [[gnu::packed]] TGAFooter
        {
            uint32_t ExtensionOffset;
            uint32_t DeveloperAreaOffset;
            char Signature[18];
        };

        static_assert(sizeof(TGAHeader) == 18,
                      "Invalid TGA header layout; padding might have been inserted by the compiler.");
        static_assert(sizeof(TGAFooter) == 26,
                      "Invalid TGA footer layout; padding might have been inserted by the compiler");

        TGAHeader Header = {};
        Header.IDLength = 0;  // no ID field
        Header.ColorMap = 0;  // no color map
        Header.ImageType = 2; // Uncompressed true-color image
        Header.Unused[0] = Header.Unused[1] = Header.Unused[2] = Header.Unused[3] = Header.Unused[4] = 0;
        Header.XOrigin = 0;
        Header.YOrigin = 0;
        Header.Width = Width;
        Header.Height = Height;
        Header.PixelDepth = BytesPerPixel * 8;
        Header.Descriptor = (1 << 5) | 8; // Top to bottom instead of bottom to top, 8 bits per alpha channel

        TGAFooter Footer = {};
        Footer.ExtensionOffset = 0;     // No extension area
        Footer.DeveloperAreaOffset = 0; // No developer area
        std::strcpy(Footer.Signature, "TRUEVISION-XFILE.");

        auto* File = std::fopen(Name.c_str(), "w");
        if (!File)
            return false;

        size_t TotalBytes = Width * Height * BytesPerPixel;
        if (!std::fwrite(&Header, sizeof(Header), 1, File))
            return false;
        if (!std::fwrite(Data, TotalBytes, 1, File))
            return false;

        return true;
    }
} // namespace Geode

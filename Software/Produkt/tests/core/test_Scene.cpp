

#include <zip.h>
#include <iostream>
#include <vector>

TEST(Scene, Zip) {
    int err = 0;

    // Open ZIP file
    zip_t* za = zip_open("data.zip", ZIP_RDONLY, &err);
    if (!za) {
        std::cerr << "Failed to open zip\n";
        return 1;
    }

    // List entries
    zip_int64_t num_entries = zip_get_num_entries(za, 0);
    std::cout << "Entries: " << num_entries << "\n";

    for (zip_uint64_t i = 0; i < num_entries; ++i) {
        const char* name = zip_get_name(za, i, 0);
        std::cout << " - " << name << "\n";
    }

    // Read one file
    zip_file_t* f = zip_fopen(za, "example.txt", 0);
    if (!f) {
        std::cerr << "Cannot open file in zip\n";
        zip_close(za);
        return 1;
    }

    // Read into memory
    std::vector<char> buf(1024);
    zip_int64_t bytes = zip_fread(f, buf.data(), buf.size());
    zip_fclose(f);

    std::cout << "\nRead " << bytes << " bytes:\n";
    std::cout.write(buf.data(), bytes);
    std::cout << "\n";

    zip_close(za);
}

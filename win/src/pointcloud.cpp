//
// Created by leioukupo on 2024/6/2.
//
#include <fstream>

// Function to convert depth frame to point cloud and save to file
void savePointCloud(const ImiImageFrame *frame, const char *filename) {
    std::ofstream file(filename);

    const uint16_t *pDepth = (const uint16_t *)frame->pData;
    int height = frame->height;
    int width = frame->width;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x, ++pDepth) {
            // Convert depth pixel (x, y, depth) to 3D point (X, Y, Z)
            // Here you might need to use the actual parameters of your depth sensor
            float X = (x - width / 2.0f) * (*pDepth) / width;
            float Y = (y - height / 2.0f) * (*pDepth) / height;
            float Z = *pDepth;

            // Write the point to the file
            file << X << " " << Y << " " << Z << "\n";
        }
    }

    file.close();
}

// Update keyboard function
void keyboardFun(unsigned char key, int32_t x, int32_t y) {
    switch (key) {
        case 'S':
        case 's':
            g_bSave = true;
            break;
        case 'd':
        case 'D':
            // Get the current frame
            ImiImageFrame *pFrame = nullptr;
            if (0 == imiReadNextFrame(g_streams[0], &pFrame, 100)) {
                // Save the point cloud
                savePointCloud(pFrame, "1.txt");
                // Release the frame
                imiReleaseFrame(&pFrame);
            }
            break;
        default:
            printf("Please input 's' or 'S' to save image, 'd' or 'D' to save point cloud: \n");
            break;
    }
}
#include "../functions.h"
#define N 8
#define M 64
#define Image vector<vector<unsigned long>>
using namespace std;

double mean_squared_error(Image img1, Image img2)
{
    double mse = 0;
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            int m = img1[i][j];
            int n = img2[i][j];
            int diff = abs(int(m - n));
            mse += (diff * diff * 1.0 / (N * N));
        }
    }
    cout << fixed << "mean squared error: " << mse << endl;
    return mse;
}

unsigned long extract(Image stego)
{
    bitset<M> msg(0);
    int k = 0;
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            bitset<M> pixel(stego[i][j]);
            msg[k++] = pixel[0];
        }
    }
    cout << "\nExtracted Msg in Binary: " << msg << endl;
    return msg.to_ulong();
}

Image embed(int msg, Image image)
{
    bitset<M> msg_binary(msg);
    Image stego(N, vector<unsigned long>(N));
    int k = 0;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
        {
            bitset<M> pixel(image[i][j]);
            pixel[0] = msg_binary[k++];
            stego[i][j] = pixel.to_ulong();
        }
    return stego;
}

void peak_signal_to_noise_ratio(Image img1, Image img2, double mse)
{
    double psnr = 10 * log10(255 * 255.0 / mse);
    cout << "Peak signal to Noise Ratio: " << psnr << endl;
}

int main()
{
    ifstream input("Input.txt");
    Image image(N, vector<unsigned long>(N));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            input >> image[i][j];
    int_fast64_t msg;
    input >> msg;
    Image stego_image = embed(msg, image);
    cout << "\n-------------------------Original Image--------------------------------" << endl;
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            cout << image[i][j] << " ";
        }
        cout << endl;
    }
    cout << "-------------------------Stego Image--------------------------------" << endl;
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            cout << stego_image[i][j] << " ";
        }
        cout << endl;
    }
    unsigned long extracted = extract(stego_image);
    cout << "Original Msg: " << msg << endl;
    cout << "Extracted Msg: " << extracted << endl;
    double mse = mean_squared_error(image, stego_image);
    peak_signal_to_noise_ratio(image, stego_image, mse);

    return 0;
}
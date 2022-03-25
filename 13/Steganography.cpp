#include "../functions.h"
#define N 8
#define M 192
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

string extract(Image stego, int bit)
{
    bitset<M> msg(0);
    int k = 0;
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            bitset<M> pixel(stego[i][j]);
            for (int l = 0; l < bit; ++l)
                msg[k++] = pixel[l];
            if (k >= msg.size())
                break;
        }
        if (k >= msg.size())
            break;
    }
    return msg.to_string();
}

Image embed(string msg, Image image, int bit)
{
    bitset<2> value(1);
    int k = 0;
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            bitset<M> pixel(image[i][j]);
            for (int l = 0; l < bit; ++l)
            {
                if (msg[k++] == '1')
                    pixel[l] = value[0];
                else
                    pixel[l] = value[1];
            }
            image[i][j] = pixel.to_ulong();
            if (k >= msg.length())
                break;
            // cout<stego[i][j]<<endl;
        }
        if (k >= msg.size())
            break;
    }
    return image;
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
    string msg;
    input >> msg;
    int bit;
    input >> bit;
    cout << bit << endl;
    ofstream output("Output.txt");
    Image stego_image = embed(msg, image, bit);
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
            output << stego_image[i][j] << " ";
        }
        output << endl;
        cout << endl;
    }
    string extracted = extract(stego_image, bit);
    cout << "Used bits: " << bit << endl;
    cout << "Original Msg: " << msg << endl;
    cout << "Extracted Msg: " << extracted << endl;
    double mse = mean_squared_error(image, stego_image);
    peak_signal_to_noise_ratio(image, stego_image, mse);

    return 0;
}
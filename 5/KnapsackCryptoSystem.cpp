#include <bits/stdc++.h>
#include "../functions.h"
using namespace std;

/**************************************************************
 CODE WORKS FOR NUMBER TILL 65535
 ***********************************************************/

unsigned long long m, w;

vector<int> generateSuperIncresingArray(int size)
{
	vector<int> array(size);
	array[0] = 1 + rand() % 5;
	srand(time(0));
	array[1] = array[0] + (1 + rand() % 5);
	int nextNum = array[0] + array[1];
	for (int i = 2; i < size; ++i)
	{
		srand(time(0));
		array[i] = nextNum + 1;
		nextNum += array[i];
	}
	return array;
}

string convertToBinary(int msg)
{
	bitset<16> binaryNum(msg); // convert 16 bit binary num
	string temp, binary = "";
	temp = binaryNum.to_string(); //from int to str

	//removing extra zeros from number because of 16 bit num
	int i;
	for (i = 0; i < temp.length(); ++i)
	{
		if (temp[i] == '1')
			break;
	}
	binary = temp.substr(i, temp.length());
	return binary;
}

int power(int num, int pow)
{
	if (pow == 0)
		return 1;
	else
		return (num * power(num, pow - 1));
}

pair<vector<int>, vector<int>> keyGeneration(vector<int> _a)
{
	srand(time(0));
	m = accumulate(_a.begin(), _a.end(), 0) + (1 + rand() % 5);
	vector<int> a(_a.size());
	for (int i = 2; i < m; ++i)
	{
		if (gcdUsingEEA(i, m) == 1) //check gcd using extended euclidian
		{
			w = i;
			break;
		}
	}
	for (int i = 0; i < _a.size(); ++i)
	{
		a[i] = (w * _a[i]) % m;
	}
	return make_pair(a, _a);
}

int encryption(vector<int> key, string msg)
{
	unsigned int encryptedMsg = 0;
	for (int i = 0; i < msg.length(); ++i)
	{
		if (msg[i] == '1')
			encryptedMsg += key[i];
	}
	return encryptedMsg;
}

string decryption(vector<int> key, int encryptedMsg)
{
	int sum = (multiplicativeInverse(w, m) * encryptedMsg) % m;
	cout << "sum: " << sum << endl;
	char decryptedBinary[key.size() + 1];
	decryptedBinary[key.size()] = '\0';
	for (int i = key.size() - 1; i >= 0; i--)
	{
		if (sum >= key[i])
		{
			decryptedBinary[i] = '1';
			sum -= key[i];
		}
		else
			decryptedBinary[i] = '0';
	}
	return decryptedBinary;
}

void print(vector<int> arr)
{
	for (int i = 0; i < arr.size(); ++i)
		cout << arr[i] << " ";
	cout << endl;
}

unsigned int convertToDecimal(string decryptedBinary)
{
	int num = 0;
	int j = 0;
	for (int i = decryptedBinary.length() - 1; i >= 0; i--)
	{
		if (decryptedBinary[i] == '1')
		{
			num += power(2, j++);
		}
		else if (decryptedBinary[i] == '0')
			j++;
	}
	return num;
}

int main()
{
	int msg;
	cout << "Enter your msg: ";
	cin >> msg;
	if (msg > 65635)
	{
		cout << "Number limit excided" << endl;
		exit(0);
	}
	string binaryMsg = convertToBinary(msg);
	//I'll generate super increasing array of size of binary representation
	int size = binaryMsg.length();
	cout << "Binary: " << binaryMsg << endl;
	vector<int> a = generateSuperIncresingArray(size);
	pair<vector<int>, vector<int>> keys = keyGeneration(a);
	cout << "m: " << m << "\tW: " << w << endl;
	vector<int> publicKey /**{21,45,75,53}**/, privateKey /**{5,15,25,50}**/;
	//extracting private and public key from keys pair
	publicKey = keys.first;
	privateKey = keys.second;
	cout << "Private Key: ";
	print(privateKey);
	cout << "Public Key: ";
	print(publicKey);
	int encryptedMsg = encryption(publicKey, binaryMsg);
	cout << "Encrypted Msg:" << encryptedMsg << endl;
	string decryptedBinary = decryption(privateKey, encryptedMsg);
	cout << "Decrypted Binary: " << decryptedBinary << endl;
	cout << "Decrypted Msg: " << convertToDecimal(decryptedBinary) << endl;
	return 0;
}

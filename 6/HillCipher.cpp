#include "functions.h"
#define matrix vector<vector<int>>

/**
 *  This code is for encryption and decryption of Hill Cipher
 *  I hardcoded the keys for this because finding matrix which
    has multiplicative inverse is more complex process.
 *  This code works for three sizes of key matrix : 2,3,4;
 *  Input to the code is size of key matrix and message(plain text)
 *  Output is Decrypted and encrypted text as well as matrices and
 *  keyMatrix used
 **/

/** sir's example key matrix 
 * keyMatrix
 * {
        {9, 7, 11, 13},
        {4,7,5,6},
        {2,21,14,9},
        {3,23,21,8}
    };
 * */

int doMod26(int num)
{
    while (num < 26)
        num += 26;
    return num % 26;
}

matrix getCofactor(matrix mat, int p, int q)
{
    //cout<<"fat start"<<endl;
    int i = 0, j = 0, n = mat.size();
    matrix cofactorMat(n - 1, vector<int>(n - 1));
    //here we are making matrix of same size
    //as a cofactor matrix that's why we are
    //going to reduce size because other elements
    //are going to be eliminated as we move forward
    for (int row = 0; row < n; ++row)
    {
        for (int col = 0; col < n; ++col)
        {
            //copying elements which not in the same row and column
            if (row != p && col != q)
            {
                cofactorMat[i][j++] = mat[row][col];
                //if row is full we move to next row and initilize col
                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
    //cout<<"fat end"<<endl;
    return cofactorMat;
}

int determinant(matrix mat, int size)
{
    //cout<<"determinant start"<<endl;
    int n = mat.size(), d = 0;
    //base case : matrix having only one element
    if (size == 1)
        return mat[0][0];
    int sign = 1;
    matrix cofactorMat(n, vector<int>(n));
    //for each element in first row
    for (int col = 0; col < size; ++col)
    {
        //cofactor for mat[0][col] (each element in first row)
        //getCofactor(matrix,rowNum,colNum);for which element you want cofactor
        cofactorMat = getCofactor(mat, 0, col);
        //we need to pass new size because in determinant because every time
        //we find cofactor size decreases by one dimention of matrix
        d += sign * mat[0][col] * determinant(cofactorMat, n - 1);
        sign = -1 * sign;
    }
    //cout<<"determinant end"<<endl;
    return doMod26(d);
}

matrix adjointMatrix(matrix mat)
{
    //cout<<"adjoint start"<<endl;
    int n = mat.size();
    if (n == 1)
    {
        mat[0][0] = 1;
        return mat;
    }
    int sign = 1;
    matrix cofactorMat(n, vector<int>(n)), adjointMat(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            //get cofactor
            cofactorMat = getCofactor(mat, i, j);
            //sign = +ve if (i+j) is even
            sign = ((i + j) % 2 == 0) ? 1 : -1;
            //get Transpose of cofactor matrix
            adjointMat[j][i] = sign * (determinant(cofactorMat, n - 1));
            adjointMat[j][i] = doMod26(adjointMat[j][i]);
        }
    }
    //cout<<"Adjoint Finished"<<endl;
    return adjointMat;
}

matrix findInverseMatrix(matrix mat)
{
    int n = mat.size(), inverseDet = multiplicativeInverse(determinant(mat, n), 26);
    matrix adjointMat(n, vector<int>(n));
    matrix inverseMat(n, vector<int>(n));
    adjointMat = adjointMatrix(mat);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            inverseMat[i][j] = doMod26(adjointMat[i][j] * (inverseDet));
        }
    }
    return inverseMat;
}

matrix generateKeyMatrix(int size)
{
    matrix keyMatrix;
    if (size == 2)
    {
        matrix key{{7, 11}, {8, 11}};
        keyMatrix = key;
    }
    else if (size == 3)
    {
        matrix key{{7, 25, 11}, {4, 18, 1}, {3, 18, 1}};
        keyMatrix = key;
    }
    else if (size == 4)
    {
        matrix key{
            {9, 7, 11, 13},
            {4, 7, 5, 6},
            {2, 21, 14, 9},
            {3, 23, 21, 8}};
        keyMatrix = key;
    }
    return keyMatrix;
}

void printMatrix(matrix mat)
{
    for (int i = 0; i < mat.size(); ++i)
    {
        for (int j = 0; j < mat[0].size(); ++j)
            cout << mat[i][j] << " ";
        cout << endl;
    }
}

matrix generatePlainTextMatrix(string plainText, int column)
{
    int row = ceil(plainText.length() * 1.0 / column);
    matrix plainTextMatrix(row, vector<int>(column));
    if ((row * column) > plainText.length())
    {
        int diff = (row * column) - plainText.length();
        while (diff--)
        {
            plainText += 'z';
        }
    }
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < column; ++j)
            plainTextMatrix[i][j] = int(plainText[column * i + j] - 'a');
    }
    return plainTextMatrix;
}

matrix encryption(matrix keyMatrix, matrix plainTextMatrix)
{
    //Here resultant matrix will be same size as plainTextMatrix
    int row = plainTextMatrix.size(), column = plainTextMatrix[0].size();
    matrix cipherTextMatrix(row, vector<int>(column));
    int temp = 0;
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < column; ++j)
        {
            for (int k = 0; k < column; ++k)
            {
                temp += ((plainTextMatrix[i][k] * keyMatrix[k][j]));
            }
            cipherTextMatrix[i][j] = (temp % 26);
            temp = 0;
        }
    }
    return cipherTextMatrix;
}

string convertToText(matrix mat)
{
    string text = "";
    for (int i = 0; i < mat.size(); ++i)
    {
        for (int j = 0; j < mat[0].size(); ++j)
            text += mat[i][j] + 'a';
    }
    return text;
}

string decryption(matrix cipherTextMatrix, matrix keyMatrix)
{

    int n = keyMatrix.size(), row = cipherTextMatrix.size();
    matrix decryptedMatrix(row, vector<int>(n));
    matrix inverseMat(n, vector<int>(n));
    inverseMat = findInverseMatrix(keyMatrix);
    int temp = 0;
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            for (int k = 0; k < n; ++k)
            {
                temp += ((cipherTextMatrix[i][k] * inverseMat[k][j]));
            }
            decryptedMatrix[i][j] = doMod26(temp);
            temp = 0;
        }
    }
    cout << "Decrypted Matrix: \n";
    printMatrix(decryptedMatrix);
    return convertToText(decryptedMatrix);
}

int main()
{
    string plainText, decryptedText;
    int size;
    cout << "Enter PlainText: ";
    cin >> plainText;
    cout << "Enter size of key Matrix (2,3 or 4): ";
    cin >> size;
    if (size > 4 || size < 2)
    {
        cout << "size is not valid" << endl;
        exit(0);
    }
    matrix keyMatrix, plainTextMatrix, cipherTextMatrix;
    keyMatrix = generateKeyMatrix(size);
    plainTextMatrix = generatePlainTextMatrix(plainText, size);
    cout << "KeyMatrix: \n";
    printMatrix(keyMatrix);
    cout << "\nPlain Text Matrix: \n";
    printMatrix(plainTextMatrix);
    cipherTextMatrix = encryption(keyMatrix, plainTextMatrix);
    cout << "Encryption Matrix: \n";
    printMatrix(cipherTextMatrix);
    cout << "Encrypted Text: " << convertToText(cipherTextMatrix) << endl;
    decryptedText = decryption(cipherTextMatrix, keyMatrix);
    cout << "Decrypted Text: " << decryptedText << endl;
    return 0;
}

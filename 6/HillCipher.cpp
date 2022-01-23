#include <bits/stdc++.h>
#define matrix vector<vector<int>>
using namespace std;

/** sir's example key matrix 
 * keyMatrix
 * {
        {9, 7, 11, 13},
        {4,7,5,6},
        {2,21,14,9},
        {3,23,21,8}
    };
 * */

vector<int> Z26 = {1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23, 25};

matrix getCofactor(matrix mat,int p,int q)
{
    //cout<<"fat start"<<endl;
    int i=0,j=0, n = mat.size();
    matrix cofactorMat(n-1,vector<int>(n-1));
    //here we are making matrux of same size
    //as a cofactor matrix that's why we are 
    //going to reduce size because other elements
    //are going to be eliminated as we move forward
    for(int row = 0 ; row < n ; ++row)
    {
        for(int col = 0; col < n ; ++col)
        {
            //copying elements which not in the same row and column
            if(row != p && col !=q)
            {
                cofactorMat[i][j++] = mat[row][col];
                //if row is full we move to next row and initilize col
                if(j == n-1)
                {
                    j=0;
                    i++;
                }
            }
        }
    }
    //cout<<"fat end"<<endl;
    return cofactorMat;
}

int determinant(matrix mat,int size)
{
    //cout<<"determinant start"<<endl;
    int n=mat.size(),d = 0;
    //base case : matrix having only one element
    if(size==1)
        return mat[0][0];
    int sign = 1;
    matrix cofactorMat(n,vector<int>(n));
    //for each element in first row
    for(int col=0 ; col<size ; ++col)
    {
        //cofactor for mat[0][col] (each element in first row)
        //getCofactor(matrix,rowNum,colNum);for which element you want cofactor
        cofactorMat = getCofactor(mat,0,col);
        //we need to pass new size because in determinant because every time
        //we find cofactor size decreases by one dimention of matrix
        d += sign*mat[0][col]*determinant(cofactorMat,n-1);
        sign = -1*sign;
    }
    //cout<<"determinant end"<<endl;
    return d;
}

matrix adjointMatrix(matrix mat)
{
    //cout<<"adjoint start"<<endl;
    int n = mat.size();
    if(n == 1)
    {
        mat[0][0] = 1;    
        return mat;
    }
    int sign = 1;
    matrix cofactorMat(n,vector<int>(n)),adjointMat(n,vector<int>(n));
    for(int i=0 ; i<n ; ++i)
    {
        for(int j=0 ; j<n ; ++j)
        {
            //get cofactor
            cofactorMat = getCofactor(mat,i,j);
            //sign = +ve if (i+j) is even
            sign = ((i+j) % 2 == 0)?1:-1;
            //get Transpose of cofactor matrix
            adjointMat[j][i] = sign*(determinant(cofactorMat,n-1));
        }
    }
    //cout<<"Adjoint Finished"<<endl;
    return adjointMat;
}

vector<vector<float>> findInverseMatrix(matrix mat)
{
    //cout<<"Inverse Start"<<endl;
    int n = mat.size(),det = determinant(mat,n);
    if(det == 0)
    {
        cout<<"Singular matrix can't find out it's inverse"<<endl;
        exit(0);
    }
    matrix adjointMat(n,vector<int>(n));
    vector<vector<float>> inverseMat(n,vector<float>(n));
    adjointMat = adjointMatrix(mat);
    for(int i=0 ; i<n ; ++i)
    {
        for(int j=0 ; j<n ; ++j)
            inverseMat[i][j] = 1.0*adjointMat[i][j] / float(det);
    }
    //cout<<"Inverse end"<<endl;
    return inverseMat;
}

matrix generateKeyMatrix(int size)
{
    matrix key(size, vector<int>(size));
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
        {
            //srand(time(0));
            key[i][j] = Z26[rand() % 12];
        }
    return key;
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

void printfMatrix(vector<vector<float>> mat)
{
    for (int i = 0; i < mat.size(); ++i)
    {
        for (int j = 0; j < mat[0].size(); ++j)
            cout << mat[i][j] << " ";
        cout << endl;
    }
}

matrix generatePlainTextMatrix(string plainText,int column)
{
    int row = ceil(plainText.length()*1.0 / column);
    //cout<<"row"<<row<<endl;
    matrix plainTextMatrix(row,vector<int>(column));
    if((row*column) > plainText.length())
    {
        int diff = (row*column) - plainText.length();
        while(diff--)
        {
            plainText += 'z';
        }
    }
    for(int i=0 ; i<row ; ++i)
    {
        for(int j=0 ; j<column ; ++j)
            plainTextMatrix[i][j] = int(plainText[column*i + j] - 'a');
    }
    return plainTextMatrix;
}

matrix encryption(matrix keyMatrix,matrix plainTextMatrix)
{
    //Here resultant matrix will be same size as plainTextMatrix
    int row = plainTextMatrix.size(),column = plainTextMatrix[0].size(); 
    matrix cipherTextMatrix(row,vector<int>(column));
    //matrix multiplication
    int temp = 0;
    for(int i=0 ;  i<row ; ++i)
    {
        for(int j=0 ; j<column ; ++j)
        {
            for(int k=0 ; k<column ; ++k)
            {
                //cout<<"\np="<<plainTextMatrix[i][k]<<"\tk="<<keyMatrix[k][j];
                temp += ((plainTextMatrix[i][k]*keyMatrix[k][j]));
            }
            //cout<<"\nNew\n";
            cipherTextMatrix[i][j] = (temp % 26);
            temp = 0;
        }
    }
    return cipherTextMatrix;
}

string decryption(matrix cipherTextMatrix,matrix keyMatrix)
{

    int n = keyMatrix.size(),row = cipherTextMatrix.size();
    //cout<<"n:"<<n<<"\trow:"<<row<<endl;
    string decryptedText = "";
    vector<vector<float>> decryptedMatrix(row,vector<float>(n));
    vector<vector<float>> inverseMat(n,vector<float>(n));
    inverseMat = findInverseMatrix(keyMatrix);
    //cout<<"Hel";
    float temp = 0;
    for(int i=0 ;  i<row ; ++i)
    {
        //cout<<"Hello from dec1";
        for(int j=0 ; j<n ; ++j)
        {
           // cout<<"Hello from dec2";
            for(int k=0 ; k<n ; ++k)
            {
            //    cout<<"Hello from dec";
                //cout<<"\np="<<plainTextMatrix[i][k]<<"\tk="<<keyMatrix[k][j];
                temp += ((cipherTextMatrix[i][k]*inverseMat[k][j]));
            }
            //cout<<"\nNew\n";
            decryptedMatrix[i][j] = temp;
            decryptedText += char(fmod(decryptedMatrix[i][j],26) + 'a') ;
            temp = 0;
        }
    }
    cout<<"Print Decrypted Matrix: \n";
    printfMatrix(decryptedMatrix);
    return decryptedText;
}

int main()
{
    string plainText="codeisready",decryptedText;
    int size=4;
    // cout<<"Enter PlainText: ";
    // cin >> plainText;
    // cout<<"Enter size of key Matrix: ";
    // cin>>size;
    matrix keyMatrix,plainTextMatrix,cipherTextMatrix;
    keyMatrix = generateKeyMatrix(size);
    plainTextMatrix = generatePlainTextMatrix(plainText,size);
    cout<<"KeyMatrix: \n";
    printMatrix(keyMatrix);
    cout<<"\nPlainText: \n";
    printMatrix(plainTextMatrix);
    cipherTextMatrix = encryption(keyMatrix,plainTextMatrix);
    cout<<"Encryption Matrix: \n";
    printMatrix(cipherTextMatrix);
    decryptedText = decryption(cipherTextMatrix,keyMatrix);
    cout<<"Decrypted Text: "<<decryptedText<<endl;
    //  matrix test{{9,7,11,13},{4,7,5,6},{2,21,14,9},{3,23,21,8}};
    // printMatrix(adjointMatrix(test));
    //  printfMatrix(findInverseMatrix(test));
    //  cout<<"done may be"<<endl;
    return 0;
}

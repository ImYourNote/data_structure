#include <stdio.h>
#include <math.h>

#pragma warning(disable: 4996 4326 6031)

#define	N	110

void main()
{
	void MakeMagicSquare(int nMagicSqr[][N], int nN);
	void ShowMagicSquare(int nMagicSqr[][N], int nN);
	void CheckMagicSquare(int nMagicSqr[][N], int nN);

	int nN;
	static int nMagicSqr[N][N];
	while (1) {
		printf("? ");
		scanf("%d", &nN);
		if (nN <= 2 || nN > N)
			break;
		MakeMagicSquare(nMagicSqr, nN);
		ShowMagicSquare(nMagicSqr, nN);
		CheckMagicSquare(nMagicSqr, nN);
		putchar('\n');
	}
	printf("Bye, ....\n");
}

void MakeMagicSquare(int nMagicSqr[][N], int nN)
{
    void InitMagicSquare(int nMagicSqr[][N], int nN);
    void OddMagicSquare(int nMagicSqr[][N], int nN, int nOrgRow, int nOrgCol, int nBgn);
    void DblyEvenMagicSquare(int nMagicSqr[][N], int nN);
    void SnglyEvenMagicSquare(int nMagicSqr[][N], int nN);

	InitMagicSquare(nMagicSqr, nN);
	if (nN % 2)
		OddMagicSquare(nMagicSqr, nN, 0, 0, 1);
	else
	{
		if (nN % 4 == 2)
			SnglyEvenMagicSquare(nMagicSqr, nN);
		else
			DblyEvenMagicSquare(nMagicSqr, nN);
	}
}


static char sRowFmt[] = "행 %1d";
static char sColFmt[] = "열 %1d";
static char sDglFmt[] = "대 %1c";
static char sCllFmt[] = "%1d ";

void InitMagicSquare(int nMagicSqr[][N], int nN)
{
	for (int nRow = 0; nRow < nN; nRow++)
		for (int nCol = 0; nCol < nN; nCol++)
			nMagicSqr[nRow][nCol] = 0;

	sRowFmt[4] = sColFmt[4] = sDglFmt[4] = (int)log10(nN - 1) + 0x31;
	sCllFmt[1] = (int)log10(nN * nN) + 0x31;
}

void OddMagicSquare(int nMagicSqr[][N], int nN, int nOrgRow, int nOrgCol, int nBgn)
{
	int nRow = nOrgRow;
	int nCol = nOrgCol + nN/2;
	int nCell = nN * nN;

	nMagicSqr[nRow][nCol] = nBgn++;

	for (int i = 1; i < nCell; ++i, ++nBgn)
	{
		int nPrvRow = nRow, nPrvCol = nCol;

		nRow = ((nRow - 1 + nN) % nN) + nOrgRow;
		nCol = ((nCol + 1) % nN) + nOrgCol;

		if (nMagicSqr[nRow][nCol])
		{
			nRow = ((nPrvRow + 1) % nN) + nOrgRow;
			nCol = nPrvCol;
		}
		nMagicSqr[nRow][nCol] = nBgn;
	}
}




void DblyEvenMagicSquare(int nMagicSqr[][N], int nN)
{
	int n = 1;
	int k = nN / 4;
	for (int i = 0; i < nN; ++i)
	{
		for (int j = 0; j < nN; ++j)
			nMagicSqr[i][j] = n++;
	}
	n = nN * nN;
	for (int i = 0; i < nN; ++i)
	{
		for (int j = 0; j < nN; ++j)
		{
			if (i == j)
				nMagicSqr[i][j] = n;

			else if ((i + j + 1) % 4 == 0)
				nMagicSqr[i][j] = n;

			else if ((i - j) % 4 == 0 || (j - i) % 4 == 0)
				nMagicSqr[i][j] = n;

			n--;
		}
	}
}




void SnglyEvenMagicSquare(int nMagicSqr[][N], int nN)
{	
	static int nOrg[4][2];
	int nH = nN / 2, nQ = nH / 2, nSqr = nH * nH;
	nOrg[1][0] = nOrg[1][1] = nOrg[2][1] = nOrg[3][0] = nH;
	for (int i = 0; i < 4; i++)			
		OddMagicSquare(nMagicSqr, nH, nOrg[i][0], nOrg[i][1], i * nSqr + 1);
	void SwitchHalf(int nMagicSqr[][N], int nCol, int nHalf);
	for (int nCol = 0; nCol < nQ; nCol++)
		SwitchHalf(nMagicSqr, nCol, nH);
	void Swap(int& x, int& y);
	Swap(nMagicSqr[nQ][0], nMagicSqr[nQ + nH][0]);		
	Swap(nMagicSqr[nQ][nQ], nMagicSqr[nQ + nH][nQ]);	
	for (int nCol = nH + nQ + 2; nCol < nN; nCol++)
		SwitchHalf(nMagicSqr, nCol, nH);
}

void SwitchHalf(int nMagicSqr[][N], int nCol, int nHalf)
{
	void Swap(int& x, int& y);
	for (int nRow = 0; nRow < nHalf; nRow++)
		Swap(nMagicSqr[nRow][nCol], nMagicSqr[nRow + nHalf][nCol]);
}

void Swap(int& x, int& y)
{
	int t = x;
	x = y;
	y = t;
}

void ShowMagicSquare(int nMagicSqr[][N], int nN)
{
	printf("\n[마방진]\n");
	for (int nRow = 0; nRow < nN; nRow++) {
		for (int nCol = 0; nCol < nN; nCol++)
			printf(sCllFmt, nMagicSqr[nRow][nCol]);
		putchar('\n');
	}
}

void CheckMagicSquare(int nMagicSqr[][N], int nN)
{
	void CheckMagicSquareRow(int nMagicSqr[][N], int nN);
	void CheckMagicSquareCol(int nMagicSqr[][N], int nN);
	void CheckMagicSquareDgl(int nMagicSqr[][N], int nN, int nDir);

	CheckMagicSquareRow(nMagicSqr, nN);
	CheckMagicSquareCol(nMagicSqr, nN);
	printf("\n[대각선 검사]\n");
	CheckMagicSquareDgl(nMagicSqr, nN, '\\');
	CheckMagicSquareDgl(nMagicSqr, nN, '/');
}

void CheckMagicSquareRow(int nMagicSqr[][N], int nN)
{
	printf("\n[행 검사]\n");
	for (int nRow = 0; nRow < nN; nRow++) {
		printf(sRowFmt, nRow);
		int nSum = 0;
		for (int nCol = 0; nCol < nN; nCol++) {
			printf("%c ", nCol ? '+' : ':');
			printf(sCllFmt, nMagicSqr[nRow][nCol]);
			nSum += nMagicSqr[nRow][nCol];
		}
		printf("= %d\n", nSum);
	}
}

void CheckMagicSquareCol(int nMagicSqr[][N], int nN)
{
	printf("\n[열 검사]\n");
	for (int nCol = 0; nCol < nN; nCol++) {
		printf(sColFmt, nCol);
		int nSum = 0;
		for (int nRow = 0; nRow < nN; nRow++) {
			printf("%c ", nRow ? '+' : ':');
			printf(sCllFmt, nMagicSqr[nRow][nCol]);
			nSum += nMagicSqr[nRow][nCol];
		}
		printf("= %d\n", nSum);
	}
}

void CheckMagicSquareDgl(int nMagicSqr[][N], int nN, int nDir)
{
	int nSum = 0, isSlash = nDir == '/';
	int nCol = isSlash * (nN - 1), nDelta = 1 - isSlash * 2;
	printf(sDglFmt, nDir);
	for (int nRow = 0; nRow < nN; nRow++, nCol += nDelta) {
		printf("%c ", nRow ? '+' : ':');
		printf(sCllFmt, nMagicSqr[nRow][nCol]);
		nSum += nMagicSqr[nRow][nCol];
	}
	printf("= %d\n", nSum);
}
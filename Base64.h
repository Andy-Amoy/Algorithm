#pragma once


const char *Base64Table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

//Tansfer RawData string to Base64 string EncodedData, 
//the calling function must ensure there is enough space for the EncodedData
void Base64Encode(char  * RawData, char * EncodedData)
{
	int StringLength=0;
	int	LoopCount;
	int RemindCount;
	char * ptmp = RawData;
	while (*ptmp != '\0')
	{
		StringLength++;
		ptmp++;
	}
	LoopCount = StringLength / 3;
	RemindCount = StringLength % 3;
	//char * ctmp = (char*)malloc(sizeof(char)*StringLength*2);

	for (int i = 0;i < LoopCount; ++i)
	{
		EncodedData[i * 4] = Base64Table[int(RawData[i * 3] >> 2)];
		EncodedData[i * 4 + 1] = Base64Table[((RawData[i * 3] << 4) & 0x30) + ((RawData[i * 3 + 1] >> 4) & 0x0F)];
		EncodedData[i * 4 + 2] = Base64Table[((RawData[i * 3 + 1] << 2) & 0x3C) + ((RawData[i * 3 + 2] >> 6) & 0x03)];
		EncodedData[i * 4 + 3] = Base64Table[(RawData[i * 3 + 2] & 0x3F)];
	}

	switch (RemindCount)
	{
	case 0:
		return;
	case 1:
		EncodedData[LoopCount * 4]= Base64Table[RawData[LoopCount * 3] >> 2];
		EncodedData[LoopCount * 4 + 1] = Base64Table[RawData[LoopCount * 3] << 4 & 0x30];
		EncodedData[LoopCount * 4 + 2] = '=';
		EncodedData[LoopCount * 4 + 3] = '=';
		return;
	case 2:
		EncodedData[LoopCount * 4] = Base64Table[RawData[LoopCount * 3] >> 2];
		EncodedData[LoopCount * 4 + 1] = Base64Table[(RawData[LoopCount * 3] << 4 & 0x30) + (RawData[LoopCount * 3 + 1] >> 4 & 0x0F)];
		EncodedData[LoopCount * 4 + 2] = Base64Table[(RawData[LoopCount * 3 + 1] << 2) & 0x3C];
		EncodedData[LoopCount * 4 + 3] = '=';
		return;

	}

}

//Tansfer Base64 string EncodedData to RawData string, 
//the calling function must ensure there is enough space for the RawData
void Base64Decode(char * EncodedData, char * RawData)
{
	int StringLength = 0;
	int	LoopCount;

	char * ptmp = EncodedData;
	while (*ptmp != '\0')
	{
		StringLength++;
		ptmp++;
	}
	LoopCount = StringLength / 4;
	for (int i = 0;i < LoopCount; ++i)
	{
		int tmp[4];
		for (int j = 0; j < 4;++j)
		{
			if (EncodedData[i * 4 + j]>='A' && EncodedData[i * 4 + j] <= 'Z')
				tmp[j] = int(EncodedData[i * 4 + j] - 'A') ;
			else if(EncodedData[i * 4 + j]>='a' && EncodedData[i * 4 + j] <= 'z')
				tmp[j] = int(EncodedData[i * 4 + j] - 'a') + 26; 
			else if (EncodedData[i * 4 + j] >= '0' && EncodedData[i * 4 + j] <= '9')
				tmp[j] = int(EncodedData[i * 4 + j] - '0') + 52;
			else if (EncodedData[i * 4 + j] == '+')
				tmp[j] = 62;
			else if (EncodedData[i * 4 + j] == '/')
				tmp[j] = 63;
			else if (EncodedData[i * 4 + j] == '=')
				tmp[j] = 0;
		}
		RawData[i * 3] = unsigned char((tmp[0] << 2&0xFC) + (tmp[1] >> 4&0x03));
		RawData[i * 3 + 1] = unsigned char((tmp[1] << 4&0xF0) + (tmp[2] >> 2&0x0F));
		RawData[i * 3 + 2] = unsigned char((tmp[2] << 6&0xC0) + (tmp[3]&0x3F));
	}
	return;
}

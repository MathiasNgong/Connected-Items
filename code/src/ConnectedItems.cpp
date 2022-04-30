/*
 *      Author: kompalli
 */
#include "ConnectedItems.h"
#include <iterator>
#include <stdlib.h>
#include <map>
#include<string>
#include<set>
#include <iomanip>    
using namespace std;

	map<int, int> sorted;
	map<int, map<int, int> > Heads;
	map<int, int> sizeMap;

      map<int, int>nMap;

void ConnectedItems::getConnectedItems(char *inputFilePath, char *outputFilePath)
{
	FILE *inFileStream = fopen(inputFilePath, "r");
	if (!inFileStream)
	{
		char message[1024];
		sprintf(message, "Cannot open input file for reading: %s", inputFilePath);
		throw std::ios_base::failure(message);
	}

	FILE *outFileStream = fopen(outputFilePath, "w");
	if (!outFileStream)
	{
		char message[1024];
		sprintf(message, "Cannot open output file for writing: %s", outputFilePath);
		throw std::ios_base::failure(message);
	}

	LogManager::writePrintfToLog(LogManager::Level::Status,
								 "ConnectedItems::getConnectedItems",
								 "Starting to process file %s", inputFilePath);
	


		while (!feof(inFileStream))
	{
		
		if (!feof(inFileStream))
		{			//Variable declaration
			char input1[255];
			int x1, y1, x2, y2, grpNum;
			fgets(input1, 255, inFileStream); // reading the lines

			if (input1[0] == '\n')
			{
				continue;
			}

			std::string s = input1;
			s.replace(0, 1, ""); //deleting the first braket
			int len = s.length() - 1;
			s.replace(len, 1, ""); //deleting the last bracket
			char a[20];
			strcpy(a, s.c_str()); //strcpy uses token varable to extract data using , as delimiter
			char *token = strtok(a, ",");
			x1 = atoi(token);
			token = strtok(NULL, ",");
			y1 = atoi(token);
			token = strtok(NULL, ",");
			x2 = atoi(token);
			token = strtok(NULL, ",");
			y2 = atoi(token);
			token = strtok(NULL, ",");
			grpNum = atoi(token);
			int CNR1 = (x1 * 10000) + y1;
			int CNR2 = (x2 * 10000) + y2;
			int aaaa=CNR1;
			string strCNR1=to_string(aaaa);
			while(strCNR1.length() < 10 )
			{strCNR1  = "0" + strCNR1;	}
			// std::cout << " (" << x1 << "," << y1 << ", CNR1 :" << CNR1 << "," << x2 << "," << y2 << ", CNR2 : " << CNR2 << "  grp num :  " << grpNum <<" new cnr1 :"<<strCNR1<< std::endl;
		
			sorted.insert({CNR1, CNR2});

			
	}
	}

		while(!sorted.empty()){
			// cout<<sorted.size()<<"size \n";
			int newHead=(*sorted.begin()).first;
			int nextVal=(*sorted.begin()).second;
			// std::cout<< (*sorted.begin()).first<<": "<< (*sorted.begin()).second<<std::endl;
			int loopHead=newHead;
			Heads[newHead][loopHead]=nextVal;
			sorted.erase(loopHead);
				loopHead=nextVal;
				nextVal= sorted[nextVal];

			while(nextVal != 0){
				Heads[newHead][loopHead]=nextVal;
				//  cout<<loopHead<<" , erase "<<nextVal<< sorted[loopHead]<<endl;
				 sorted.erase(loopHead);
				loopHead=nextVal;
				nextVal= sorted[nextVal];
				// cout<<loopHead<<" , "<<nextVal<<endl;
				
			}
			sizeMap[newHead]=Heads[newHead].size();
			 sorted.erase(loopHead);
		}
	// map<int, map<int, int> >::iterator itr;

	map<int, int>::iterator ptr;

	

	// for (itr = Heads.begin(); itr != Heads.end(); itr++) {

	// 	for (ptr = itr->second.begin(); ptr != itr->second.end(); ptr++) {
	// 		// cout << "First key is " << itr->first
	// 		// 	<< " And second key is " << ptr->first
	// 		// 	<< " And value is " << ptr->second << endl;
	// 	}
	// }

	for (map<int, int>::iterator ptr = sizeMap.begin(); ptr != sizeMap.end(); ptr++) {
			// cout << "First key is " << itr->first
				// cout<< " And second key is " << ptr->first
				// << " And value is " << ptr->second << endl;

				nMap[ptr->second*-1] = ptr->first;
		}


	
	// 	for (map<int, int>::iterator ptr = nMap.begin(); ptr != nMap.end(); ptr++) {
	// 		// cout << "First key is " << itr->first
	// 			cout<< " And second key is " << ptr->first
	// 			<< " And value is " << ptr->second << endl;
	// 	}
	fprintf(outFileStream, "Format: (x1, y1, x2, y2, group number)\n");
int grpNom=0;
map<int,int>::iterator ii=nMap.begin();
while(  ii!=nMap.end())  
   {  
	   grpNom++;
    //    cout << (*ii).first << ": wat " << (*ii).second << endl;  
	ptr = Heads[(*ii).second].begin();
	   while( ptr != Heads[(*ii).second].end()) {

				// cout<<"("<<ptr->first<<", "<<ptr->second<<", "<< grpNom<<")"<<endl;
				int px1=ptr->first/10000;
				int py1 = ptr->first%10000;
				int px2=ptr->second/10000;
				int py2 = ptr->second%10000;
				// cout<<"("<<px1<<", "<<py1<<", "<<px2<<", "<<py2<<", "<< grpNom<<")"<<endl;

					string printS="("+to_string(px1)+", "+to_string(py1)+", "+to_string(px2)+", "+to_string(py2)+", "+ to_string(grpNom)+")\n";
			fprintf(outFileStream, "%s", printS.c_str());
			ptr++;



		}

		 ++ii;


   }  



	fflush(outFileStream);
	fclose(outFileStream);

	fclose(inFileStream);
}
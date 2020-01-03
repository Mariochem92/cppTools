#include <iostream>
#include <fstream>
#include <string.h>
#include <cstring>
#include <stdio.h>
#include <chrono>
#include <time.h>
#include "gnuplot-iostream.h"
int main(){
        std::ifstream infile;
	std::string inFileName="spese.dat";
	std::vector<double> spese(8*12);
	infile.open(inFileName.c_str(), std::ios_base::in);
    	if (infile.is_open())  
    	{
        	for (int i = 0; i < 12*8; i++) 
        	{
		infile >> spese[i];
		//std::cout << spese[i] << "\n";
        	}	
        infile.close(); // CLose input file
   	 }	
    	else { //Error message
		std::cout << "Can't find input file " << inFileName << "\n";
    		}
	time_t now = time(0);	
 	tm *ltm = localtime(&now);
	int month= ltm->tm_mon;
	std::cout<<"mese e anno: "<<month+1<<"/"<<1900 + ltm->tm_year<<"\n";
	std::cout<< "Hai fatto spese oggi?(s/n)"<<"\n";
	std::string risp;
	std::cin>>risp;
	int d=1;
	if (risp == "n"){std::cout<<"Bravo, risparmia!"<<"\n";}
	else {
		while( d <= 8) {std::cout<<"ok, hai speso in 1-cibo 2-trasporti 3-divertimento serale 4-cultura 5-viaggi 6-vizi 7-vestiti 8-spesa 10-nient'altro"<<"\n";
	std::cin>>d;
	if (d>8){break;};
	int soldi;
	d=d-1;
	std::cout<<"Quanto hai speso?"<<"\n";
	std::cin>>soldi;
	std::cout<<month*8+d<<"pointer\n";
	std::cout<<spese[month*8+d]<<"\n";
	spese[month*8+d]=spese[month*8+d]+soldi;
	std::cout<<spese[month*8+d]<<"\n";
		}
	}
	//infile.open(inFileName.c_str(), std::ios_base::in);
	std::ofstream myfile (inFileName);
	if (myfile.is_open())
        {
                for (int i = 0; i < 12*8; i++)
                {
			if ((i+1)%8==0){myfile<<spese[i]<< "\n";}
			else {myfile<<spese[i]<< " ";}

                }
        myfile.close(); // CLose input file
         }
	std::vector<std::pair <double,double> > xy_pts;
	std::vector<std::pair <double,double> > xy_cont;
		for (int j=0;j<8;j++)
		{
		xy_pts.push_back(std::make_pair(j, spese[month*8+j]));
		}
		Gnuplot gp;
		gp << "set terminal wxt 0 size 900,600\n";
		gp << "set boxwidth 0.5 absolute\n";
		gp << "set title 'Spese di questo mese €'\n";
		gp << "set xtics border in scale 0,0 nomirror rotate by -45 autojustify\n";
		gp << "set xtics ('cibo' 0, 'trasporti' 1, 'divertimento serale' 2, 'cultura' 3, 'viaggi' 4, 'vizi' 5, 'vestiti' 6,  'spesa' 7)\n";
		gp << "p '-' u 1:2 w boxes fill p 1 ls 3 t '' \n";
    		gp.send1d(xy_pts);
		gp << "set yrange [0:MAX=GPVAL_Y_MAX*1.1];set xrange [GPVAL_X_MIN-0.1:GPVAL_X_MAX+0.1]\n";
		gp << "refresh\n";

		gp << "set title 'Spese di questo anno €'\n";
		gp << "set yrange [0:11];set xrange [0:7]\n";
		gp << "set terminal wxt 1 \n";
		gp << "set xtics border in scale 0,-1 nomirror rotate by -45 autojustify\n";
		gp << "set pm3d  map interpolate 20,20; splot 'spese.dat' matrix \n";


}


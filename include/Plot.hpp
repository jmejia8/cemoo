#ifndef PLOT_H
#define PLOT_H

#include <string>
#include <fstream>
#include <sstream>
#include "population.hpp"

class Plot
{
public:
	Plot (){
	}
	virtual ~Plot (){

	}

	void scatter(Individual* population, int population_size)
	{

		std::ifstream template_file("plot/template.html");
		std::ofstream html_file("plot/tmp.html");
		std::string template_str = "";
		std::string line;
		int dimension = population[0].get_nfs();

		if (population == NULL) 
			error("Plot: empty population.");

		int j = 0;
		while (std::getline(template_file, line)) {
			++j;
			if (j != 12) {
				html_file << line << std::endl;
				continue;
			}
			


			if (dimension == 2) {
				html_file << "type: 'scatter',\n";
			}else if (dimension == 3) {	
				html_file << "type: 'scatter3d',\n";
			}


			// ============================
			// ============== X ===========
			// ============================
			html_file << "x: [";
			// x data here
			for (int i = 0; i < population_size; ++i) {
				html_file << population[i].f[0]  << "," ;
			}
			html_file << "],\n";

			// ============================
			// ============== Y ============
			// ============================
			html_file << "y: [";
			// y data here
			for (int i = 0; i < population_size; ++i) {
				html_file << population[i].f[1]  << "," ;
			}
			html_file << "],";


			// ============================
			// ============== Z ===========
			// ============================
			if (dimension < 3) {
				continue;
			}
			html_file << "z: [";
			// z data here

			for (int i = 0; i < population_size; ++i) {
				html_file << population[i].f[2]  << "," ;
			}
			html_file << "],";

		}
		

		html_file.close();
		template_file.close();


	}

	void show()
	{
		system("open plot/tmp.html");
		system("exo-open plot/tmp.html");
	}

private:
};


#endif

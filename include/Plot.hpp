#ifndef PLOT_H
#define PLOT_H

#include <string>
#include <fstream>
#include <sstream>
#include "population.hpp"

class Plot
{
private:
	std::ifstream template_file;
	std::ofstream html_file;

public:
	Plot (){
		template_file.open("plot/template.html");
		html_file.open("plot/tmp.html");
	}
	virtual ~Plot (){
		template_file.close();
		html_file.close();
	}

	void plot_many_objectives(Individual* population, int population_size)
	{
		int m = population[0].get_nfs();

		for (int i = 0; i < population_size; ++i) {

			html_file <<  "var trace" << i << " = {\n";
			html_file << "type: 'scatter', mode: 'lines',\n";
			html_file << "y: [ ";
			for (int j = 0; j < m; ++j) {
				html_file << population[i].x[j] << ",";
			}
			html_file << "],\n";
			html_file << "};\n";
		}
		
		html_file << "var data = [ ";
		for (int i = 0; i < population_size; ++i) {
			html_file <<  "trace" << i << ",";
		}
		html_file << " ];\n";

		
	}

	void plot_fvalues3(Individual* population, int population_size){
			html_file <<  "var trace1 = {\n";
			int dimension = population[0].get_nfs();

			if (dimension == 2) {
				html_file << "type: 'scatter', mode: 'markers',\n";
            
			}else if (dimension == 3) {	
				html_file << "type: 'scatter3d', mode: 'markers' ,\n";
			}else if (dimension > 3)
				html_file << "type: 'scatter', mode: 'lines', \n";


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
			html_file << "],\n";


			// ============================
			// ============== Z ===========
			// ============================
			if (dimension == 3) {
				html_file << "z: [";
				// z data here

				for (int i = 0; i < population_size; ++i) {
					html_file << population[i].f[2]  << "," ;
				}
				html_file << "],\n";
			}
			
			html_file << "};\n\n";
			html_file << "var data = [ trace1 ];\n";
        

	}

	void scatter(Individual* population, int population_size)
	{

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

			if (dimension > 3)
				plot_many_objectives(population, population_size);
			else
				plot_fvalues3(population, population_size);
			

		}
		

	}


	void show()
	{
		system("open plot/tmp.html");
		system("exo-open plot/tmp.html");
		std::cout << "Opening plot/tmp.html in your web browser" << std::endl;
	}
};


#endif

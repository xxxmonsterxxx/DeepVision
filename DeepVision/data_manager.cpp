#include "data_manager.h"
#include "deepvsn.h"

#include <string>
#include <fstream>
#include <iostream>

Data_Manager::Data_Manager()
{

}

void Data_Manager::load_data(const GLchar * name_wfn, const GLchar * name_cpt)
{
	using namespace std;

	string tmp;
	ifstream inp(name_wfn);

	getline(inp, tmp);

	inp >> tmp >> numberOfAtoms	>> tmp >> tmp >> numberOfAtoms >> tmp >> numberOfAtoms >> tmp;

	atoms = new atom[numberOfAtoms];
	for (int i = 0; i < numberOfAtoms; i++)
	{
		getline(inp, tmp);
		float x,y,z,charge;
		inp >> tmp >> tmp >> tmp >> tmp >> x >> y >> z >> tmp >> tmp >> charge;
		atoms[i].pos_x = x;
		atoms[i].pos_y = y;
		atoms[i].pos_z = z;
		atoms[i].charge = charge;
	}

	inp.close();


	char S;
	inp.open(name_cpt);

	while (tmp != "BCPs")
	{
		getline(inp, tmp);
		inp >> tmp >> tmp;
	}
	inp >> tmp >> numberOfBonds;
	map = new int*[numberOfBonds];

	for (int i = 0; i < numberOfBonds; i++)
		map[i] = new int[2];

	while (tmp != "BONDS" && !inp.eof())
	{
		getline(inp, tmp);
		for (int i = 0; i<4; i++) inp >> tmp;
	}
	for (int j = 0; j<3; j++) getline(inp, tmp);

	bonds = new bond_cp[numberOfBonds];


	for (int i = 0; i < numberOfBonds; i++)
	{
		cout << tmp;
		bond_cp &b = bonds[i];
		for (int j = 0; j < 9; j++)
			inp >> tmp;
		inp >> b.a_ind >> tmp >> b.b_ind >> tmp;
		getline(inp, tmp);
		inp >> tmp >> tmp >> b.pos_x >>
			tmp >> tmp >> b.pos_y >> 
			tmp >> tmp >> b.pos_z;

		for (int j = 0; j < 6; j++)
			getline(inp, tmp);
	}
}

void Data_Manager::draw(DeepVision *wdgt)
{
	for (int i = 0; i < numberOfAtoms; i++)
	{
			int ind = (atoms[i].charge - 1) * 5;
			wdgt->addSphere(glm::vec3(atoms[i].pos_x, atoms[i].pos_y, atoms[i].pos_z), periodic[ind + 1] * 0.01,
				glm::vec3(periodic[ind + 2] / 255., periodic[ind + 3] / 255., periodic[ind + 4] / 255.));
	}

	for (int i = 0; i < numberOfBonds; i++)
	{
		int inda = bonds[i].a_ind - 1;
		int indb = bonds[i].b_ind - 1;
		glm::vec3 left = glm::vec3(atoms[bonds[i].a_ind - 1].pos_x, atoms[bonds[i].a_ind - 1].pos_y, atoms[bonds[i].a_ind - 1].pos_z);
		glm::vec3 right = glm::vec3(atoms[bonds[i].b_ind - 1].pos_x, atoms[bonds[i].b_ind - 1].pos_y, atoms[bonds[i].b_ind - 1].pos_z);
		wdgt->addCylinder(right, left, 0.05);
		wdgt->addSphere(glm::vec3(bonds[i].pos_x, bonds[i].pos_y, bonds[i].pos_z), 0.1, glm::vec3(1.f,0.f,0.f));
	}
}
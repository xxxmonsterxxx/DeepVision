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

	getline(inp, tmp);
	inp >> tmp >> tmp >> tmp >> this->nummberOfRCPs;
	getline(inp, tmp);
	inp >> tmp >> tmp >> tmp >> this->nummberOfCCPs;

	while (tmp != "BONDS" && !inp.eof())
	{
		getline(inp, tmp);
		for (int i = 0; i < 4; i++) inp >> tmp;
	}
	for (int j = 0; j<3; j++) getline(inp, tmp);

	bonds = new bond_cp[numberOfBonds];


	for (int i = 0; i < numberOfBonds; i++)
	{
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

	while (tmp != "RINGS" && !inp.eof())
	{
		getline(inp, tmp);
		for (int i = 0; i < 4; i++) inp >> tmp;
	}

	for (int j = 0; j < 4; j++) getline(inp, tmp);

	for (int i = 0; i < this->nummberOfRCPs; i++)
	{
		float x, y, z;
		inp >> tmp >> tmp >> x
			>> tmp >> tmp >> y
			>> tmp >> tmp >> z;

		ring_cp.push_back(glm::vec3(x, y, z));

		for (int j = 0; j < 7; j++)
			getline(inp, tmp);
	}

	while (tmp != "CAGES" && !inp.eof())
	{
		getline(inp, tmp);
		for (int i = 0; i < 3; i++) inp >> tmp;
	}
	
	for (int j = 0; j < 4; j++) getline(inp, tmp);


	for (int i = 0; i < this->nummberOfCCPs; i++)
	{
		float x, y, z;
		inp >> tmp >> tmp >> x
			>> tmp >> tmp >> y
			>> tmp >> tmp >> z;
		std::cout << x << y << z;
		cage_cp.push_back(glm::vec3(x, y, z));

		for (int j = 0; j < 7; j++)
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
		wdgt->addSphere(glm::vec3(bonds[i].pos_x, bonds[i].pos_y, bonds[i].pos_z), 0.08, glm::vec3(1.f,0.f,0.f));
	}


	for (int i = 0; i < numberOfBonds; i++)
	{
		std::vector<glm::vec3> points;
		int inda = bonds[i].a_ind - 1;
		int indb = bonds[i].b_ind - 1;
		glm::vec3 left = glm::vec3(atoms[bonds[i].a_ind - 1].pos_x, atoms[bonds[i].a_ind - 1].pos_y, atoms[bonds[i].a_ind - 1].pos_z);
		glm::vec3 midle = glm::vec3(bonds[i].pos_x, bonds[i].pos_y, bonds[i].pos_z);
		glm::vec3 right = glm::vec3(atoms[bonds[i].b_ind - 1].pos_x, atoms[bonds[i].b_ind - 1].pos_y, atoms[bonds[i].b_ind - 1].pos_z);
		points.push_back(left);
		points.push_back(midle);
		points.push_back(right);
		wdgt->addPolyLine(points, glm::vec3(0.f, 1.f, 0.f));
	}

	for (int i = 0; i < this->nummberOfRCPs; i++)
	{
		wdgt->addSphere(ring_cp[i], 0.08, glm::vec3(1.f, 1.f, 0.f));
	}

	for (int i = 0; i < this->nummberOfCCPs; i++)
	{
		wdgt->addSphere(cage_cp[i], 0.08, glm::vec3(0.5f, 0.9f, 0.5f));
	}
}

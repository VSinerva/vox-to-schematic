#include "vox_reader.h"

using namespace std;

void readInt(uint32_t &integer, istream &file)
{
	file.read(reinterpret_cast<char*>(&integer), sizeof(integer));
}	

void readByte(uint8_t &byte, istream &file)
{
	file.read(reinterpret_cast<char*>(&byte), sizeof(byte));
}	

//TEMP!
//Rotation not implemented
uint8_t readRotation(std::istream &file)
{
	return uint8_t{0};
}

vector<int> readTranslation(std::istream &file)
{
	uint32_t stringLength;
	uint8_t byte;
	int tempInt{0};
	vector<int> translation;

	//.vox stores translations as strings of Base10 numbers (ugh)
	//Read string character by character
	readInt(stringLength, file);
	for(int i{0}; i < stringLength; ++i)
	{
		readByte(byte, file);

		//Spaces denote the end of a number and the start of another
		if(byte == ' ')
		{
			translation.push_back(tempInt);
			tempInt = 0;
		}

		//If the same number continues, everything before this point needs to be "shifted to the right" (*10)
		//Then the new characters value is added to the total
		//Digits in ASCII are sequential starting from '0' at 48 so the actual numeric value is the ASCII code -48
		else
		{
			tempInt *= 10;
			tempInt += byte - '0';
		}
	}

	//Push the last number into the vector
	translation.push_back(tempInt);

	return translation;
}

uint32_t tagToInt32(char a, char b, char c, char d)
{
	return (a | b<<8 | c<<16 | d<<24);
}


bool isHeaderValid(istream &file)
{
	uint32_t temp_uint32;

	//Check the file is a vox file by checking for:
	//1) Starts with "VOX "
	//2) Followed by version number 150
	//3) Content starts with "MAIN"
	readInt(temp_uint32, file);
	if(temp_uint32 != tagToInt32('V', 'O', 'X', ' '))
	{
		cerr << "File does not appear to be a valid .vox file (No or incorrect filetype in header)\n";
		return false;
	}

	readInt(temp_uint32, file);
	if(temp_uint32 != 150)
	{
		cerr << "File does not appear to be a valid .vox file (No or incorrect version number)\n";
		return false;
	}

	readInt(temp_uint32, file);
	if(temp_uint32 != tagToInt32('M', 'A', 'I', 'N'))
	{
		cerr << "File does not appear to be a valid .vox file (No MAIN)\n";
		return false;
	}

	//Skip chunk info after "MAIN" tag (8 bytes)
	file.seekg(8, ios::cur);

	return true;
}

vector<model> readModels(istream &file)
{
	uint32_t tag{0};
	uint32_t sizeTag	{ tagToInt32( 'S', 'I', 'Z', 'E') };

	vector<model> models{};
	int id{0};
	uint32_t size_x;
	uint32_t size_y;
	uint32_t size_z;

	uint32_t nOfModels;
	uint8_t x{0};
	uint8_t y{0};
	uint8_t z{0};
	uint8_t colByte{0};

	//Read tag for next chunk
	readInt(tag, file);

	while(tag == sizeTag )
	{
		//Skip chunk info after "SIZE" tag (8 bytes)
		file.seekg(8, ios::cur);

		readInt(size_x, file);
		readInt(size_y, file);
		readInt(size_z, file);

		models.push_back( model(id++, size_x, size_y, size_z));

		//Skip "XYZI" tag and its chunk info (12 bytes)
		file.seekg(12, ios::cur);

		readInt(nOfModels, file);
		for( int i{0}; i < nOfModels; ++i)
		{
			readByte(x, file);
			readByte(y, file);
			readByte(z, file);
			readByte(colByte, file);
			models.back().data[x][y][z].colorIndex = colByte;
		}

		//Read tag for next chunk
		readInt(tag, file);
	}

	//Move back before last read chunk id
	file.seekg(-4, ios::cur);

	return models;
}

node readTranslationNode(istream &file)
{
	uint32_t dictSize{0};
	uint8_t byte{0};

	uint32_t childId;
	vector<int> translation(3, 0);
	uint8_t rotation;

	//TEMP!
	//Assume no node attributes(_name and _hidden)
	//Skip node attributes (4 bytes)
	file.seekg(4, ios::cur);

	readInt(childId, file);

	//Skip reserved id, layer id and num of frames (12 bytes)
	file.seekg(12, ios::cur);

	//Read frame attributes
	readInt(dictSize, file);
	for(int i{0}; i < dictSize; ++i)
	{
		//Rotation and translation can be differentiated based on a single byte
		//Skip bytes before that (5 bytes)
		file.seekg(5, ios::cur);

		readByte(byte, file);

		if(byte == 'r')
			rotation = readRotation(file);
		else if(byte == 't')
			translation = readTranslation(file);
	}

	node temp;
	temp.childNodes.push_back(childId);
	temp.translation_x = translation[0];
	temp.translation_y = translation[1];
	temp.translation_z = translation[2];
	temp.rotation = rotation;

	return temp;
}

node readGroupNode(istream &file)
{
	uint32_t nOfChildren;
	uint32_t childId;

	//TEMP!
	//Assume no node attributes(_name and _hidden)
	//Skip node attributes (4 bytes)
	file.seekg(4, ios::cur);

	readInt(nOfChildren, file);

	node temp;
	for(int i{0}; i < nOfChildren; ++i)
	{
		readInt(childId, file);
		temp.childNodes.push_back(childId);
	}

	return temp;
}

node readShapeNode(istream &file)
{
	uint32_t modelId;

	//TEMP!
	//Assume no node attributes(_name and _hidden)
	//Skip node attributes (4 bytes)
	file.seekg(4, ios::cur);

	//Skip num of models because it is always 1 (4 bytes)
	file.seekg(4, ios::cur);

	readInt(modelId, file);

	node temp;
	temp.modelId = modelId;

	//Skip  model attribute because it is always empty (reserved) (4 bytes)
	file.seekg(4, ios::cur);

	return temp;
}

vector<node> readNodes(istream &file)
{
	uint32_t tag{0};

	uint32_t transformTag{ tagToInt32( 	'n', 'T', 'R', 'N') };
	uint32_t groupTag{ tagToInt32( 			'n', 'G', 'R', 'P') };
	uint32_t shapeTag{ tagToInt32( 			'n', 'S', 'H', 'P') };

	vector<node> nodes{};
	uint32_t nodeId;

	while(true)
	{
		//Read tag for next chunk
		readInt(tag, file);

		if(tag == transformTag || tag == groupTag || tag == shapeTag)
		{
			readInt(nodeId, file);

			//Place node in the vector of nodes with an index == nodeId
			//First ensure vector is large enough, resize if necessary
			if(nodes.size() < nodeId+1)
				nodes.resize(nodeId + 1);

			if(transformTag)
				nodes[nodeId] = readTranslationNode(file);
			else if(groupTag)
				nodes[nodeId] = readGroupNode(file);
			else if(shapeTag)
				nodes[nodeId] = readShapeNode(file);
		}

		else
			break;
	}

	//Move back before last read chunk id
	file.seekg(-4, ios::cur);

	return nodes;
}

void applyRotations(std::vector<node> nodes, std::vector<model> &models)
{
	//Make sure there is no empty space at the end of the nodes vector
	nodes.shrink_to_fit();

	node currentNode;
	for(int nodeId{0}; nodeId < nodes.size(); ++nodeId)
	{
		currentNode = nodes[nodeId];
		for(int childId : currentNode.childNodes)
		{
			nodes[childId].rotate(currentNode.rotation);
		}
	}

	for(node &node : nodes)
	{
		//modelId defaults to -1 and can never be -1 if it has been read from a file
		//This checks if the nodes modelId has been set to an actual value
		if(node.modelId != -1)
			models[node.modelId].rotate(node.rotation);
	}
}

void applyTranslations(std::vector<node> nodes, std::vector<model> &models)
{
	//Make sure there is no empty space at the end of the nodes vector
	nodes.shrink_to_fit();

	node currentNode;
	for(int nodeId{0}; nodeId < nodes.size(); ++nodeId)
	{
		currentNode = nodes[nodeId];
		for(int childId : currentNode.childNodes)
		{
			nodes[childId].translate(currentNode.translation_x, currentNode.translation_y, currentNode.translation_z);
		}
	}

	for(node &node : nodes)
	{
		//modelId defaults to -1 and can never be -1 if it has been read from a file
		//This checks if the nodes modelId has been set to an actual value
		if(node.modelId != -1)
			models[node.modelId].translate(node.translation_x, node.translation_y, node.translation_z);
	}
}

intMatrix_t modelsToMatrix(std::vector<model> models)
{
}

intMatrix_t readVoxFile( char* filepath)
{
	ifstream file;

	file.open(filepath, ios::binary);

	if(file.is_open())
	{
		if(isHeaderValid(file) == false)
			return intMatrix_t{}; 

		//Read models
		vector<model> models{readModels(file)};

		//Read nodes
		vector<node> nodes{readNodes(file)};

		//Apply rotations from nodes to models
		applyRotations(nodes, models);

		//Apply translations from nodes to models
		applyTranslations(nodes, models);

		file.close();

		return modelsToMatrix(models); 
	}

	cerr << "Unable to read file\n";
	return intMatrix_t{}; 
}

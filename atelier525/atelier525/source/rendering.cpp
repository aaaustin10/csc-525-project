#include "includes.h"

const int tex_size = 16;
unsigned char line_tex[tex_size][tex_size][3];

void rendering::grid()
{
	glBegin(GL_LINES);
	{
		glColor3f(0.1, 0.8, 0.1);
		for (int i = 0; i < 200 + 1; i++){
			glVertex3f(-100, -0.1, i - 100);
			glVertex3f(100, -0.1, i - 100);
		}
		for (int i = 0; i < 201; i++){
			glVertex3f(i - 100, -.1, -100);
			glVertex3f(i - 100, -.1, 100);
		}
	}
	glEnd();
}

GLuint rendering::init_line_algorithm()
{
	GLuint tex_id;
	glGenTextures(1, &tex_id);
	glBindTexture(GL_TEXTURE_2D, tex_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	for (int i = 0; i < tex_size; ++i)
		for (int j = 0; j < tex_size; ++j)
			for (int k = 0; k < 3; ++k)
				line_tex[i][j][k] = -1;

	return tex_id;
}

void rendering::line_algorithm()
{
	static GLuint tex_id = init_line_algorithm();
	static int curr_frame = 0;
	int speed_denom = 10;

	for (int i = 0; i < tex_size; i++)
	{
		for (int j = 0; j < 3; ++j)
		{
			unsigned char value;
			if (i <= curr_frame / speed_denom)
				value = 0;
			else
				value = -1;
			line_tex[i][i][j] = value;
		}
	}

	++curr_frame;
	curr_frame %= tex_size * speed_denom;

	glBindTexture(GL_TEXTURE_2D, tex_id);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, tex_size, tex_size, GL_RGB, GL_UNSIGNED_BYTE, line_tex);

	glEnable(GL_TEXTURE_2D);
	{
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

		glBegin(GL_QUADS);
		{
			glTexCoord2f( 1.0f,  1.0f); glVertex3f( 14.0f,  2.0f,  -10.0f);
			glTexCoord2f( 0.0f,  1.0f); glVertex3f( 16.0f,  2.0f,  -10.0f);
			glTexCoord2f( 0.0f,  0.0f); glVertex3f( 16.0f,  0.0f,  -10.0f);
			glTexCoord2f( 1.0f,  0.0f); glVertex3f( 14.0f,  0.0f,  -10.0f);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
}

enum header_type{ comment, vt, v, f, o, mtllib, usemtl, newmtl, map_Kd, notImplemented };

header_type get_header(std::string s)
{
	header_type val = notImplemented;
	if (!s.compare("#"))
		val = comment;
	else if (!s.compare("v"))
		val = v;
	else if (!s.compare("f"))
		val = f;
	else if (!s.compare("o"))
		val = o;
	else if (!s.compare("vt"))
		val = vt;
	else if (!s.compare("mtllib"))
		val = mtllib;
	else if (!s.compare("newmtl"))
		val = newmtl;
	else if (!s.compare("map_Kd"))
		val = map_Kd;
	else if (!s.compare("usemtl"))
		val = usemtl;
	return val;
}

void rendering::read_mtllib(std::stringstream& line)
{
	std::string buf, filename, head, tex_name;
	line >> buf;

	std::fstream file;
	file.open(buf, std::ios::in);
	while (std::getline(file, buf))
	{
		texture_struct t;
		std::stringstream line(buf);
		head.resize(0); // for empty lines
		line >> head;
		switch (get_header(head))
		{
		case comment:
			break;
		case newmtl:
			line >> tex_name;
			break;
		case map_Kd:
		{
			std::string temp;
			line >> temp;
			t = init_texture(temp.c_str());
			t.tex_name = tex_name;
			textures.push_back(t);
			break;
		}
		default:
			break;
		}
	}
	file.close();
}

int rendering::get_tex_index(const char* tex_name)
{
	for (unsigned int i = 0; i < textures.size(); ++i)
	{
		if (!textures[i].tex_name.compare(tex_name))
			return i;
	}
	return -1;
}

void rendering::read_obj(const char* filename)
{
	std::fstream file;
	std::string buf, head;
	file.open(filename, std::ios::in);
	if (!file.good())
	{
		std::cout << "Failed to open obj file" << std::endl;
	}

	while (std::getline(file, buf))
	{
		std::stringstream line(buf);
		line >> head;
		switch (get_header(head))
		{
		case comment:
			break;
		case v:
		{
			vertex temp;
			line >> temp.x;
			line >> temp.y;
			line >> temp.z;
			vertices.push_back(temp);
			break;
		}
		case vt:
		{
			pair temp;
			line >> temp.s;
			line >> temp.t;
			texture_verts.push_back(temp);
			break;
		}
		case f:
		{
			index_pair vtemp[3];
			for (int i = 0; i < 3; i++)
			{
				line >> vtemp[i].v;
				vtemp[i].v--;
				if (line.peek() == '/')
				{
					line.ignore(1);
					line >> vtemp[i].vt;
					vtemp[i].vt--;
				}
				else
				{
					vtemp[i].vt = -1;
				}
			}
			face temp;
			temp.v1 = vtemp[0];
			temp.v2 = vtemp[1];
			temp.v3 = vtemp[2];
			faces.push_back(temp);
			break;
		}
		case mtllib:
			read_mtllib(line);
			break;
		case usemtl:
		{
			std::string temp;
			line >> temp;
			tex_range tr;
			tr.starting_face = faces.size();
			tr.tex_index = get_tex_index(temp.c_str());
			if (tr.tex_index == -1)
			{
				std::cout << "Error in obj file." << std::endl;
				std::cout << "Erroneous line: \"" << line.str() << '"' << std::endl;
				tr.tex_index = 0;
			}
			texture_ranges.push_back(tr);
			break;
		}
		default:
			break;
		}
	}
	file.close();
}

void rendering::draw()
{
	int current_tex_range = 0;
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBegin(GL_TRIANGLES);
	{
		for (unsigned i = 0; i < faces.size(); i++)
		{
			if (texture_ranges[current_tex_range].starting_face == i)
			{
				glEnd();
				glBindTexture(GL_TEXTURE_2D, textures[texture_ranges[current_tex_range].tex_index].tex_id);
				if (current_tex_range != texture_ranges.size() - 1)
					++current_tex_range;
				glBegin(GL_TRIANGLES);
			}
			face curr_face = faces[i];
			if (curr_face.v1.vt != -1)
			{
				glTexCoord2f
					(
					texture_verts[curr_face.v1.vt].s,
					texture_verts[curr_face.v1.vt].t
					);
			}
			glVertex3f
				(
				vertices[curr_face.v1.v].x,
				vertices[curr_face.v1.v].y,
				vertices[curr_face.v1.v].z
				);
			if (curr_face.v2.vt != -1)
			{
				glTexCoord2f
					(
					texture_verts[curr_face.v2.vt].s,
					texture_verts[curr_face.v2.vt].t
					);
			}
			glVertex3f
				(
				vertices[curr_face.v2.v].x,
				vertices[curr_face.v2.v].y,
				vertices[curr_face.v2.v].z
				);
			if (curr_face.v3.vt != -1)
			{
				glTexCoord2f
					(
					texture_verts[curr_face.v3.vt].s,
					texture_verts[curr_face.v3.vt].t
					);
			}
			glVertex3f
				(
				vertices[curr_face.v3.v].x,
				vertices[curr_face.v3.v].y,
				vertices[curr_face.v3.v].z
				);
		}
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

bmp_header rendering::load_texture(const char* filename)
{
	std::ifstream input;
	input.open(filename, std::ios::binary | std::ios::in);
	if (!input.good())
	{
		std::cout << "Couldn't open file" << std::endl;
		exit(0);
	}

	input.seekg(0, std::ios::end);
	int size = input.tellg();
	input.seekg(0, std::ios::beg);

	char* buf = new char[size];
	input.read(buf, size);

	if (buf[0] != 'B' || buf[1] != 'M')
	{
		std::cout << "Verify that " << filename << " is actually a bmp" << std::endl;
		exit(0);
	}

	bmp_header header;
	header.bitmap_loc = buf;
	header.size = *((int*)(buf + 2));
	header.start_offset = *((int*)(buf + 10));
	header.width = *((int*)(buf + 18));
	header.height = *((int*)(buf + 22));
	header.data = buf + header.start_offset;
	for (int i = 0; i < size - header.start_offset; i += 3)
	{
		char temp = header.data[i];
		header.data[i] = header.data[i + 2];
		header.data[i + 2] = temp;
	}
	return header;
}

texture_struct rendering::init_texture(const char* filename)
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	texture_struct t;
	t.tex_data = load_texture(filename);
	glGenTextures(1, &t.tex_id);
	glBindTexture(GL_TEXTURE_2D, t.tex_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);

	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, t.tex_data.width, t.tex_data.height, GL_RGB, GL_UNSIGNED_BYTE, t.tex_data.data);
	delete[] t.tex_data.bitmap_loc;
	return t;
}
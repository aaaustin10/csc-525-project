#ifndef RENDERING_H

	#define RENDERING_H

	struct vertex { float x; float y; float z; };
	struct pair { float s; float t; };
	struct index_pair { int v; int vt; };
	struct face { index_pair v1; index_pair v2; index_pair v3; };
	struct bmp_header
	{
		char* bitmap_loc;
		char type[2];
		int size;
		short info1;
		short info2;
		int start_offset;
		char* data;
		int width;
		int height;
	};
	struct texture_struct { GLuint tex_id; std::string tex_name; bmp_header tex_data; };
	struct tex_range { int tex_index; int starting_face; };

	class rendering
	{
	public:
		void grid();
		void line_algorithm();
		void poly_algorithm();
		GLuint init_line_algorithm();
		void room();
		bmp_header load_texture(const char* filename);
		texture_struct init_texture(const char* filename);
		void read_obj(const char* filename);
		void draw();
		void read_mtllib(std::stringstream& line);
	private:
		int get_tex_index(const char* tex_name);
		std::vector<vertex> vertices;
		std::vector<pair> texture_verts;
		std::vector<face> faces;

		std::vector<texture_struct> textures;
		std::vector<tex_range> texture_ranges;
	};

#endif
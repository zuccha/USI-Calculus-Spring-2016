#include <iostream>
#include <fstream>
#include <vector>
#include <string>

const std::string BEGIN_BLOCK = "BEGIN_BLOCK";
const std::string END_BLOCK = "END_BLOCK";
const std::string BEGIN_PROOF = "BEGIN_PROOF";
const std::string END_PROOF = "END_PROOF";
const std::string BEGIN_EXAMPLE = "BEGIN_EXAMPLE";
const std::string END_EXAMPLE = "END_EXAMPLE";

const int BLOCK = 0;
const int PROOF = 1;
const int EXAMPLE = 2;

void generate_tex(const std::string &file, bool proofs, bool examples, bool def)
{
	std::ofstream tex_proofs("calculus_notes_proofs.tex");
	std::ofstream tex_examples("calculus_notes_examples.tex");
	std::ofstream tex_def("calculus_notes_definitions.tex");
	std::ifstream tex_source(file);

	if (proofs && !tex_proofs.is_open()) {
		proofs = false;
		std::cout << "Unable to open proofs.tex" << std::endl;
	}
	if (examples && !tex_examples.is_open()) {
		examples = false;
		std::cout << "Unable to open examples.tex" << std::endl;
	}
	if (def && !tex_def.is_open()) {
		def = false;
		std::cout << "Unable to open def.tex" << std::endl;
	}

	if(tex_source.is_open()) {
		int read = BLOCK;
		std::string line;
		while (std::getline(tex_source,line)) {
			if (line.find(BEGIN_BLOCK) != -1) {
				read = BLOCK;
			}
			else if (line.find(BEGIN_PROOF) != -1) {
				read = PROOF;
			}
			else if (line.find(BEGIN_EXAMPLE) != -1) {
				read = EXAMPLE;
			}

			if (def && read == BLOCK) {
				tex_def << line << std::endl;
			}
			if (proofs && read != EXAMPLE) {
				tex_proofs << line << std::endl;
			}
			if (examples && read != PROOF) {
				tex_examples << line << std::endl;
			}

			if (line.find(END_PROOF) != -1 || line.find(END_EXAMPLE) != -1) {
				read = BLOCK;
			}
		}
		tex_proofs.close();
		tex_examples.close();
		tex_def.close();
		tex_source.close();
	}
	else {
		std::cout << "Unable to open " << file << std::endl;
	}
}

int main()
{
	generate_tex("calculus_notes_complete.tex", true, true, true);
	return 0;
}
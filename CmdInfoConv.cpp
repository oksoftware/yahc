#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class ComInfoConv {
	private:
		std::istream *src;
		std::ostream *dst;
	private:
		std::vector<std::string> split(std::string haystack, std::string needle){
			using namespace std;
			vector<string> ret;
			for(unsigned int i = 0, n; i <= haystack.length(); i = n + 1){
				n = haystack.find_first_of(needle, i);
				if(n == string::npos) n = haystack.length();
				ret.push_back(haystack.substr(i, n - i));
			}
			return ret;
		}


	public:
		ComInfoConv(std::istream *src, std::ostream *dst){
			this->src = src;
			this->dst = dst;
			return;
		}
		void convert(){
			using namespace std;
			string curline;
			vector<string> cur;
			vector<string> cmdList;
			string strDst("");


			while(getline(*src, curline)){
				if(curline.find("#") == 0){
					continue;
				}else if(curline == "\n"){
					continue;
				}
				cur = split(curline, "\t");

				string typeName = cur.at(0);
				string cmdId = cur.at(1);
				string cmdName = cur.at(2);
				/* Currently the program won't read parameters */
				strDst += "AXCmdInfo cmd_" + cmdName + ";\n";
				strDst += "cmd_" + cmdName + ".type = TYPE_" + typeName + ";\n";
				strDst += "cmd_" + cmdName + ".id = " + cmdId + ";\n";
				strDst += "cmd_" + cmdName + ".name = \"" + cmdName + "\";\n";

				strDst += "\n";

				cmdList.push_back("cmd_" + cmdName);


			}

			*dst<<"#include \"AXStruct.h\""<<endl<<endl;
			*dst<<strDst<<endl;

			*dst<<"AXCmdInfo *cmdInfoList = {"<<endl;

			for(vector<string>::iterator i = cmdList.begin(); i != cmdList.end(); i++){
				*dst<<*i<<","<<endl;
			}
			*dst<<"NULL};"<<endl;
			*dst<<"const int cmdInfoCnt = "<<cmdList.size()<<";"<<endl;

			return;
		}
};

int main(int argc, char *argv[]){
	using namespace std;

	if(argc < 3){
		cerr<<"Error: This converter needs two filenames(input and output)"<<endl
		    <<"Usage: ComInfoConv inputfile outputfile"<<endl;
		return 1;
	}
	ifstream input(argv[1], ifstream::in);
	ofstream output(argv[2], ofstream::out);

	ComInfoConv converter(&input, &output);
	converter.convert();

	return 0;
}

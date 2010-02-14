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
			int cnt = 0;


			*dst<<"const AXCmdInfo CmdInfo::cmdInfoList[] = {"<<endl;

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

				*dst<<"\t{"<<endl;
				*dst<<"\t\ttype : TYPE_"<<typeName<<","<<endl;
				*dst<<"\t\tid : 0x"<<cmdId<<","<<endl;
				*dst<<"\t\tname : \""<<cmdName<<"\","<<endl;
				*dst<<"\t},"<<endl;
				cnt++;

			}

			*dst<<"\tNULL};"<<endl;
			*dst<<"const int CmdInfo::cmdInfoCnt = "<<cnt<<";"<<endl;

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

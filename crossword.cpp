#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

void read_dic(vector<string> &dic){

  string line;
  ifstream myfile ("word.txt");

  if (myfile.is_open())
  {
    while ( myfile.good() )
    {
		getline (myfile,line);
		dic.push_back(line);
      
    }
    myfile.close();
  }

  else cout << "Unable to open file"; 
}

void fill_grid(vector<vector<string> > &grid){
	int m;
	cin >> m;
	vector<string> row;
	string str;

	for(int j=0;j<m;j++){
		for(int i=0;i < m ; i++){
			cin >> str;
			row.push_back(str);
		}
		grid.push_back(row);
		row.clear();
	}
}

void print_grid(vector<vector<string> > grid){
	for(int i=0;i< grid.size() ; i++){
		for(int j=0;j<grid.size() ;j++){
			cout<<grid[i][j]<<" ";
		}
		cout<<endl;
	}
}

bool empty_unit(vector< vector<string> > grid,vector<int> v){

	if(v[2] == 1){
       for(int i = 0; i < v[3]; i++)
            if (grid[v[0]][i+v[1]] == "_")
                return true;
    }

    if(v[2] == -1){
       for(int i = 0; i < v[3]; i++)
            if (grid[i+v[0]][v[1]] == "_")
                return true;
    }

    return false;
}

vector<int> find_slot(vector< vector<string> > grid)
{

	int n = grid.size();

	for(int i = 0; i < n; i++) {

        for ( int j = 0; j < n ;j++) {

			if (grid[i][j] != "*") { 

				//Horizontal search for slots
				for (int k =j ;k< n; k++) {
					
					if (grid [i][k] == "*" || k == n-1){
						vector<int> v;
						int l = k - j + 1;
						if (grid[i][k] == "*" ) 
							l = k -j;

						
						if (l > 1 ) {
							v.push_back(i);
							v.push_back(j);
							v.push_back(1);
							v.push_back(l);
							if (empty_unit(grid,v))
							    return v;
						}
						break;
					}
				}

				//Vertical search for slots
				for (int k =i ;k< n; k++) {
					if ((grid [k][j] == "*" ) || k == n-1){
						vector<int> v;
						int l = k-i+1;
						if (grid[k][j] == "*" ) l = k -i;
						if ( l >1){
							v.push_back(i);
							v.push_back(j);
							v.push_back(-1);
							v.push_back(l);
							if (empty_unit(grid,v))
							    return v;
						}
						break;
					}
				}
				
			}
		}
	}

	vector<int> v;

	v.push_back(-1);
	v.push_back(-1);
	v.push_back(-1);
	v.push_back(-1);

	return v;
}

string get_str(vector<vector<string> > grid, vector<int> v){
    string word= "";
    if(v[2] == 1){
       for(int i = 0; i < v[3]; i++)

            word+=grid[v[0]][i+v[1]];
    }

    if(v[2] == -1){
       for(int i = 0; i < v[3]; i++)
            word+=grid[v[0]+i][v[1]];
    }
    return word;

}

vector<string> get_words(vector<string> dic ,string s) {
	
	
	vector<string> list;
    for (int i=0;i< dic.size();i++){
		int flag = 1;
		if ( dic[i].size() == s.size()+1){
			
			for(int j=0; j < s.size(); j++ ){
		if (s[j] != dic[i][j] && s[j] != '_') {

					flag = 0;
					break;
				}
			}
			if (flag){
				list.push_back(dic[i]);
				
			}
		}
	
	}
	return list;

}

bool only_one_blank(int a,int b, int c, vector<vector<string> > grid)
{
	int count=0;

	if( c == 1) {
		for( int i = a-1; i >= 0; i--) {
			if(grid[i][b][0] == '_')
				count++;
			if( grid[i][b][0] == '*')
				break;
		}
		for( int i = a+1; i < grid.size(); i++ ) {
			if( grid[i][b][0] == '_')
				count++;
			if( grid[i][b][0] == '*')
				break;
		}
		if( count > 0 ) { 
			return false;
		}
	}

	if( c == -1) {
		for( int i = b-1; i >= 0; i--) {
			if(grid[a][i][0] == '_')
				count++;
			if ( grid[a][i][0] == '*')
				break;
		}
		for( int i = b+1; i < grid.size(); i++ ) {
			if( grid[a][i][0] == '_')
				count++;
			if ( grid[a][i][0] == '*')
				break;
		}
		if( count > 0 ) {
			return false;
		}
	}
	return true;
}
bool find_dic(string s,vector<string> dic)
{

	for( int i =0; i < dic.size(); i++){
		string temp;
		for( int j =0;j<s.size();j++){
			temp.push_back(dic[i][j]);
					
		}
		if( temp == s) {

			return true;
		}
	}
	return false;

}
string reverse_string(string s){
	string ans;
	for(int i=s.size()-1;i>=0;i--){
		ans.push_back(s[i]);
	}
	return ans;
}
bool check_existence(int a, int b, int c ,vector<vector<string> > grid, char s,vector<string> dic)
{
	string word;
	string pre;
	if( c == 1) {
		for( int i = a-1; i >= 0; i--) {
			if(grid[i][b][0] != '*')
				pre.push_back(grid[i][b][0]);
			else
				break;
		}
		word.push_back(s);
		for( int i = a+1; i < grid.size(); i++ ) {
			if(grid[i][b][0] !='*')
				word.push_back(grid[i][b][0]);
			else
				break;
		}
		word = reverse_string(pre)+ word;
		if( find_dic(word,dic) ) { 
			return true;
		}
	}
	if( c == -1) {
		for( int i = b-1; i >= 0; i--) {
			if(grid[a][i][0] != '*')
				pre.push_back(grid[a][i][0]);
			else
				break;
		}
		word.push_back(s);
		for( int i = b+1; i < grid.size(); i++ ) {
			if(grid[a][i][0] != '*')
				word.push_back(grid[a][i][0]);
			else
				break;
			
		}
		word = reverse_string(pre) + word;
		if( find_dic(word,dic) ) { 
			return true;
		}
	}
	return false;


}

int enter_in_grid(string s, vector<int> v , vector<vector<string> >  &grid,vector<string> dic) {
    if(v[2] == 1){
       for(int i = 0; i < v[3]; i++) {
	    if( grid[v[0]][i+v[1]][0] == '_'){
		    if ( only_one_blank(v[0], v[1] + i, 1, grid) )
		       if( ! check_existence(v[0],v[1]+i,1,grid,s[i],dic)) return -1;
	    }
            grid[v[0]][i+v[1]] = s[i];
       }
            	
    }

    if(v[2] == -1){
       for(int i = 0; i < v[3]; i++) {
	    if( grid[v[0]+i][v[1]][0] == '_'){
		    if ( only_one_blank(v[0]+i, v[1], -1, grid) )
		       if ( ! check_existence(v[0]+i,v[1],-1,grid,s[i],dic)) return -1;
	    }
            grid[i+v[0]][v[1]] = s[i];
       }
    }
return 0;
}

	
void find_solution(vector<vector<string> > grid, vector<string> dic) {

	vector<int> v;
    v = find_slot(grid);
	if (v[0] == -1 && v[1] == -1 && v[2] == -1 && v[3] == -1){
		print_grid(grid);
		cout<<"Completed!"<<endl;
		exit(1) ;
	}
    string word = get_str(grid, v);

    vector<string> list_words;

    list_words = get_words(dic,word );

	//Prints all the words
#ifdef LIST
    	cout << "Word >> " << word << endl;
	cout<< "List of words for "<< word << endl;
	for( int i =0 ;i< list_words.size(); i++){
		cout << i+1 << " " << list_words[i] << endl;
	}
#endif    
	int no_of_matches = list_words.size();
	while ( !list_words.empty() ) {
#ifdef CURR
		cout <<"CURRENT_WORD >>>>>>>>>> " << list_words.back()<<endl;
#endif
	
		if(enter_in_grid (list_words.back(), v, grid,dic) == -1) {
			list_words.pop_back();
#ifdef DEBUG	
			print_grid(grid);
#endif

			continue;
		}
		else{
#ifdef DEBUG		

		print_grid(grid);
#endif
			list_words.pop_back();
		}
		find_solution(grid, dic);
	}
	return;
	
	
}	

int main()
{

	vector <string> dic;
	vector <vector <string> > grid;
	
	read_dic(dic); 									//read word.txt to generate a vector of words
    fill_grid(grid);								//inputs the square grid saving  it in vector of vector of string

						
    find_solution(grid,dic);							
//	print_grid(grid);
	
    return 0;
}

	




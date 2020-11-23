
   /*this code is form https://gist.github.com/toboqus/def6a6915e4abd66e922 */

    #include <iostream>
	#include <string.h>
	#include <string>
	#include <fstream>
	#include <sstream>
	#include <bits/stdc++.h> 


    using namespace std;

   
    typedef struct node{
    char value_char;
    node *left;
    node *right;
	node(){
		this->left=nullptr;
		this->right=nullptr;
		value_char='\0';
	}
	
    } node;

	/*trie*/
    class trie{
	public:

    int size;
    node *root;
	
	trie(){
		root=new node;
		size=1;
		}


	bool exist(node* leaf, string key, char a){
		for(int i=0;i<key.length();i++){
			if(leaf->right==nullptr && leaf->left==nullptr){
				break;
			}
			if(key.at(i)=='0' && leaf->left!=nullptr){
				leaf=leaf->left;
			}
			else if(key.at(i)=='1' && leaf->right!=nullptr){
				leaf=leaf->right;
			}
			else{
				break;
			}
		}
		if(leaf->value_char==a){//there are not equals
			return true;
		}
		return false;

	}



	int depth(node *root){
		if (root == NULL)  
        return 0;  
		else
		{  
			/* compute the depth of each subtree */
			int lDepth = depth(root->left);  
			int rDepth = depth(root->right);  
		
			/* use the larger one */
			if (lDepth > rDepth)  
				return(lDepth + 1);  
			else return(rDepth + 1);  
		}

	}





    /*remove char from a tree*/
	node *remove(node* root, string key, int depth,char a ) { 
		if (depth == key.length()) { 
			// This node is no more end of word after 
			// removal of given key 
			if (root->value_char!='\0' && root->value_char==a){ 
				root->value_char='\0'; 
			}
					// If given is not prefix of any other word 
			if (root->right==NULL && root->left==NULL) { 
				delete (root); 
				root = NULL; 
				this->size--;

			} 
			return root; 
			
		}
		
		if(key.at(depth)=='1'){
			root->right = remove(root->right, key, depth + 1,a);
		}
		if(key.at(depth)=='0'){				
			root->left = remove(root->left, key, depth + 1,a);
		}
		
		if(root->left==NULL && root->right==NULL && root->value_char=='\0' && depth>0){
			delete (root); 
				root = NULL; 
				this->size--;
		}
		return root;

	}

	
/* insert to a trie*/
	void insert(string key,  int i ,node *leaf,char a){
			if(i<key.length() && key.at(i) == '0'){
				i++;
				//left
				if(leaf->left != nullptr){
					insert(key,i, leaf->left,a);
				}else{
					leaf->left = new node;
					this->size++;
					if(i==key.length()){//at the end
						leaf->left->value_char=a;
					}else{
					insert(key,i, leaf->left,a);
					}
				}
			}
			else if(i<key.length() && key.at(i) == '1'){
				//right
				i++;
				if(leaf->right != NULL){
					insert(key,i, leaf->right,a);

				}else{
					//leaf=nullptr
					leaf->right = new node;
					this->size++;
					if(i==key.length()){
						leaf->right->value_char=a;
	
					}else{
					insert(key,i, leaf->right,a);
					}
				}
			}
		
	}	

	
	/*search-if we have 255.255.255.255 find in 255.255.255.0*/
	void search(string key, node *leaf){
		int max=0, max_temp=0;string max_s; string max_s_temp;
		for(int i=0;i<key.length();i++){
			if(leaf->value_char!='\0'){
				max_s=leaf->value_char;
				max_temp=max;
			}
			if(leaf->right==nullptr && leaf->left==nullptr){
				max_s_temp=leaf->value_char;
				break;
			}
			if(key.at(i)=='0' && leaf->left!=nullptr){
				max++;
				leaf=leaf->left;
			}
			else if(key.at(i)=='1' && leaf->right!=nullptr){
				max++;
				leaf=leaf->right;
			}
			else{
				break;
			}
		}
		if(max_s.compare(max_s_temp)!=0){//there are not equals
			max_temp++;
			cout<<" at the depth " << max_temp ;

		}
		else{
			max++;
			cout <<" at the depth " << max ;

		}


	}

		void search(string key){
			search(key, root);
		}



    void optimization(node *leaf){
	//if  the right char ==left char so replace the root 
    if(leaf->right!=nullptr && leaf->left!=nullptr){
        if(leaf->right->value_char==leaf->left->value_char){
                leaf->value_char=leaf->right->value_char;
                delete(leaf->right);
				leaf->right=NULL;
				this->size--;
                delete(leaf->left);
				leaf->left=NULL;
				this->size--;

        }
    }
	else if(leaf->right==nullptr && leaf->left!=nullptr){
		optimization(leaf->left);
	}
	else if(leaf->right!=nullptr && leaf->left==nullptr){
		optimization(leaf->right);
	}

}



			
	};

	
//covert to binary 8 numbers
	string convert(string temp){
		int tmp=stoi(temp);
		string binary=bitset<8>(tmp).to_string();
		return binary;
	}

	/*gets string like 255.255/16 or 255.255.255.0 and return the ip in binary*/
string to_binary(string s){
    string delimeter="/";
	int len;
	string ip=s.substr(0,s.find(delimeter));//split until '/'
	string length=s.substr(s.find(delimeter)+1, s.length());//length
	if(length!=""){
		 len=stoi(length);
	}
	string final_ip="";
	string temp;
	int i=0;
	while(i<ip.length()){//there is .
		while( i<ip.length() && ip.at(i)!='.' ){
			temp+=ip.at(i);
			i++;
		}
		final_ip+=convert(temp);
		temp="";
		i++;
	}
	if(len!=0 && len<final_ip.length()){
		string final_ip_1;
		i=0;
		while(final_ip_1.length()<len){
			final_ip_1+=final_ip.at(i);
			i++;
		}
		return final_ip_1;
	}
	return final_ip;

}

/* function that gets the name _file and read initalize the trie*/
void read_from_file(string name_file){
    string myText;
    ifstream MyReadFile(name_file);
    //there is a line in myText
		trie tr;

		while (getline (MyReadFile, myText)) {
			istringstream ss(myText);
			string ip;
			char result;
			string d;

			string action,prefix;
			ss>>action>>prefix>>result;

			/*read from file*/
			if(myText!=""){
				if(action.compare("ADD")==0){//ADD
					ip=to_binary(prefix);
					tr.insert(ip,0,tr.root, result);
					tr.optimization(tr.root);
					cout<<"Added "+prefix+" "+ result+" "+ "at depth "<<tr.depth(tr.root)<<" , total nodes "<<tr.size << endl;
				}
				else if(action.compare("REMOVE")==0){//REMOVE
					ip=to_binary(prefix);
					if(tr.exist(tr.root, ip, result)) {
					tr.remove(tr.root, ip,0,result);
					cout<<"Removed "<<prefix<<" at depth "<<tr.depth(tr.root)<<", total nodes "<<tr.size<<endl;
					}
					else{
					cout<<"The prefix you entered isn't exist "<<endl;
					}
				}
				else if(action.compare("FIND")==0){//FIND
					ip=to_binary(prefix);
					cout<< "Found "<<prefix;
					tr.search(ip);
					cout<<" " << endl;

				}
				else{
					throw exception();//if it doesn't a vaild action
				}
			}
		}
		MyReadFile.close();
	
}

int main(int argc, char *argv[]){
string name(argv[1]);
read_from_file(name);




// 	trie tr;
//  char result='A';
// tr.insert("1110",0,tr.root,'A');
// cout<<tr.size<<endl;
// tr.insert("1111", 0, tr.root,'A');
// cout<<tr.size<<endl;
// tr.optimization(tr.root);
// cout<<tr.size<<endl;
// tr.remove(tr.root,"111",0,'A');
// cout<<tr.size<<endl;
// tr.remove(tr.root, "1111", 0,'B');
// cout<<tr.size<<endl;
// tr.remove(tr.root, "1110", 0, 'A');
// cout<<tr.depth(tr.root)<<endl;
// cout<<tr.size<<endl;
 
 
 

   
}
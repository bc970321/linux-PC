 #include <iostream>
 #include <string>
 #include <map>
 using namespace std;
 bool judge(std::string r1, std::string r2) {
      int mathNum = 0;
      int loopNum = 0;
      int r1_start = 0;
      int i = 0;
     while (true) {
           if (loopNum > r1.size() || mathNum == r1.size()) break;
         if (r1[r1_start] == r2[i]) {
                r1_start = (r1_start + 1) % r1.size();
                i = (i + 1) % r2.size();
                mathNum++;
               
         } else {
                i = (i + 1) % r2.size();
                mathNum = 0;
               
         }
           loopNum++;
          
     } 
      return (mathNum == r2.size());

 }

 int main() {
      int n;
      std::string r1, r2, r3;
      std::cin >> n;
     while (n--) {
           std::cin >> r1 >> r2 >> r3;
           if (r1.size() != r2.size() || r1.size() != r3.size() || r2.size() != r3.size()) std::cout << "NO\n";
           if (judge(r1, r2) && judge(r1, r3)) std::cout << "YES\n";
           else std::cout << "NO\n";
          
     }
      return 0;

 }

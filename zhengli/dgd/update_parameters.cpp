#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <cstdlib>

using namespace std;

vector<string> readFile(const string& filename) {
    vector<string> lines;
    ifstream file(filename.c_str());
    
    string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }
    file.close();
    return lines;
}

void writeFile(const string& filename, const vector<string>& lines) {
    ofstream file(filename.c_str());
    
    for (size_t i = 0; i < lines.size(); i++) {
        file << lines[i] << endl;
    }
    file.close();
}

bool parseParameterLine(const string& line, string& paramName, string& value, string& error, string& constraint) {
    if (line.empty()) return false;
    
    size_t eqPos = line.find('=');
    
    paramName = line.substr(0, eqPos);

    size_t start = paramName.find_first_not_of(" \t");
    size_t end = paramName.find_last_not_of(" \t");
    if (start != string::npos && end != string::npos) {
        paramName = paramName.substr(start, end - start + 1);
    }
 
    string rest = line.substr(eqPos + 1);
    
    size_t plusMinusPos = rest.find("+/-");
    if (plusMinusPos != string::npos) {
        value = rest.substr(0, plusMinusPos);
        string afterPlusMinus = rest.substr(plusMinusPos + 3);

        size_t constraintPos = afterPlusMinus.find_first_of("CL");
        if (constraintPos != string::npos && constraintPos != 0) {
            error = afterPlusMinus.substr(0, constraintPos);
            constraint = afterPlusMinus.substr(constraintPos);
        } else {
            error = afterPlusMinus;
            constraint = "";
        }
    } else {
        size_t cPos = rest.find("C");
        size_t lPos = rest.find("L(");
        
        if (cPos != string::npos && (lPos == string::npos || cPos < lPos)) {
            value = rest.substr(0, cPos);
            constraint = rest.substr(cPos);
        } else if (lPos != string::npos) {
            value = rest.substr(0, lPos);
            constraint = rest.substr(lPos);
        } else {
            value = rest;
            constraint = "";
        }
        error = "";
    }
    
    size_t valStart = value.find_first_not_of(" \t");
    size_t valEnd = value.find_last_not_of(" \t");
    if (valStart != string::npos && valEnd != string::npos) {
        value = value.substr(valStart, valEnd - valStart + 1);
    } else {
        value = "";
    }
    
    if (!error.empty()) {
        size_t errStart = error.find_first_not_of(" \t");
        size_t errEnd = error.find_last_not_of(" \t");
        if (errStart != string::npos && errEnd != string::npos) {
            error = error.substr(errStart, errEnd - errStart + 1);
        } else {
            error = "";
        }
    }
    
    if (!constraint.empty()) {
        size_t conStart = constraint.find_first_not_of(" \t");
        size_t conEnd = constraint.find_last_not_of(" \t");
        if (conStart != string::npos && conEnd != string::npos) {
            constraint = constraint.substr(conStart, conEnd - conStart + 1);
        } else {
            constraint = "";
        }
    }
    
    return true;
}

string buildParameterLine(const string& paramName, const string& value, const string& error, const string& constraint) {
    stringstream line;
    line << paramName << " = " << value;
    
    if (!error.empty()) {
        line << " +/- " << error;
    }
    
    if (!constraint.empty()) {
        line << " " << constraint;
    }
    
    return line.str();
}

map<string, pair<string, string> > readAccDParameters(const string& filename, const string& yearSuffix) {
    map<string, pair<string, string> > accParams;
    
    vector<string> lines = readFile(filename);
   
    for (size_t i = 0; i < lines.size(); i++) {
        string paramName, value, error, constraint;
        if (parseParameterLine(lines[i], paramName, value, error, constraint)) {
            if (paramName.find("accD" + yearSuffix + "_") == 0) {
                accParams[paramName] = make_pair(value, error);
                cout << paramName << " = " << value;
                if (!error.empty()) cout << " +/- " << error;
                if (!constraint.empty()) cout << " " << constraint;
                cout << endl;
            }
        }
    }
    
    return accParams;
}

void updateAccMParameters(vector<string>& targetLines, 
                         const map<string, pair<string, string> >& accDParams,
                         const string& targetPrefix,
                         const string& yearSuffix) {
    
    for (size_t i = 0; i < targetLines.size(); i++) {
        string paramName, value, error, constraint;
        if (parseParameterLine(targetLines[i], paramName, value, error, constraint)) {
            if (paramName.find(targetPrefix + yearSuffix + "_") == 0) {
                size_t underscorePos = paramName.find_last_of('_');
                if (underscorePos != string::npos) {
                    string indexStr = paramName.substr(underscorePos + 1);
                    string sourceParamName = "accD" + yearSuffix + "_" + indexStr;

                    if (accDParams.find(sourceParamName) != accDParams.end()) {
                        const pair<string, string>& sourceValues = accDParams.at(sourceParamName);
                        string newLine = buildParameterLine(paramName, sourceValues.first, sourceValues.second, constraint);
                        targetLines[i] = newLine;
                        
                        cout << paramName << " = " << sourceValues.first;
                        if (!sourceValues.second.empty()) {
                            cout << " +/- " << sourceValues.second;
                        }
                        if (!constraint.empty()) {
                            cout << " " << constraint;
                        }
                        cout << endl;
                    } 
                }
            }
        }
    }
}

int main() {
    string targetFile = "/lzufs/user/zhanghy/dgd/dgdfit/parinfor/parinfor_base_allyears.dat";
    
    vector<string> targetLines = readFile(targetFile);
    cout << "==========================================" << endl;
    
    cout << "kst :" << endl;
    cout << "------------------------------------------" << endl;
    
    map<string, pair<string, string> > accD16_kst = readAccDParameters(
        "/lzufs/user/zhanghy/kplus/timeAcc/jpsikst/parinfor/parinfor_base_2016.dat", "16");
    updateAccMParameters(targetLines, accD16_kst, "accD_kst", "16");
    
    map<string, pair<string, string> > accD17_kst = readAccDParameters(
        "/lzufs/user/zhanghy/kplus/timeAcc/jpsikst/parinfor/parinfor_base_2017.dat", "17");
    updateAccMParameters(targetLines, accD17_kst, "accD_kst", "17");

    map<string, pair<string, string> > accD18_kst = readAccDParameters(
        "/lzufs/user/zhanghy/kplus/timeAcc/jpsikst/parinfor/parinfor_base_2018.dat", "18");
    updateAccMParameters(targetLines, accD18_kst, "accD_kst", "18");
    
    cout << "==========================================" << endl;
    
    cout << "ks :" << endl;
    cout << "------------------------------------------" << endl;
    
    map<string, pair<string, string> > accD16_ks = readAccDParameters(
        "/lzufs/user/zhanghy/kplus/timeAcc/jpsiks/parinfor/parinfor_base_2016.dat", "16");
    updateAccMParameters(targetLines, accD16_ks, "accD_ks", "16");
    
    map<string, pair<string, string> > accD17_ks = readAccDParameters(
        "/lzufs/user/zhanghy/kplus/timeAcc/jpsiks/parinfor/parinfor_base_2017.dat", "17");
    updateAccMParameters(targetLines, accD17_ks, "accD_ks", "17");

    map<string, pair<string, string> > accD18_ks = readAccDParameters(
        "/lzufs/user/zhanghy/kplus/timeAcc/jpsiks/parinfor/parinfor_base_2018.dat", "18");
    updateAccMParameters(targetLines, accD18_ks, "accD_ks", "18");
    
    cout << "==========================================" << endl;
    
    string outputFile = "/lzufs/user/zhanghy/dgd/dgdfit/parinfor_base_allyears.dat";
    writeFile(outputFile, targetLines);
    
    return 0;
}

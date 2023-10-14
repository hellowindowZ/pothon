
#include <iostream>
#include <vector>
#include <map>
#include <sstream>

typedef std::map<std::string, std::string> VariableMap;
typedef std::vector<std::string> List;

class PothonInterpreter {
public:
    void executeStatement(const std::string& statement) {
        std::istringstream iss(statement);
        auto command = std::string();
        iss >> command;

        if (command == "orint") {
            std::string value;
            std::getline(iss, value);

            if (value[0] == '$') {
                std::string variableName = value.substr(1);
                if (variables.find(variableName) != variables.end()) {
                    print(variables[variableName]);
                } else {
                    std::cout << "δ֪�ı�����" << variableName << std::endl;
                }
            }
            else if (isExpression(value)) {
                std::string result = evalExpression(value);
                print(result);
            }
            else if (value[0] == '"' && value[value.length() - 1] == '"') {
                std::string content = value.substr(1, value.length() - 2);
                print(content);
            }
            else {
                std::cout << "�޷�ʶ��Ĳ�����" << value << std::endl;
            }
        }
        else if (command == "var") {
            std::string name, value;
            iss >> name >> value;
            setVariable(name, value);
        }
        else if (command == "loop") {
            int times = 0;
            std::string code;
            iss >> times;
            std::getline(iss, code);
            loop(times, code);
        }
        else if (command == "list") {
            std::string name;
            iss >> name;
            createList(name);
        }
        else if (command == "help") {
            std::string topic;
            iss >> topic;
            showHelp(topic);
        }
        else if (command == ""){
        	std::cout << "you can enter help" << std::endl;
        }
        	
    }

    void run() {
        std::string statement;
        while (true) {
            std::cout << "> ";
            std::getline(std::cin, statement);
            executeStatement(statement);
        }
    }

private:
    VariableMap variables;
    std::map<std::string, List> lists;

    void print(const std::string& value) {
        std::cout << value << std::endl;
    }

    void setVariable(const std::string& name, const std::string& value) {
        variables[name] = value;
    }

    void loop(int times, const std::string& code) {
        for (int i = 0; i < times; ++i) {
            executeStatement(code);
        }
    }

    void createList(const std::string& name) {
        lists[name].emplace_back();
    }

    bool isExpression(const std::string& value) {
        return (value.find_first_of("+-*/") != std::string::npos);
    }

    std::string evalExpression(const std::string& expression) {
        std::istringstream iss(expression);
        int num1, num2;
        char op;

        iss >> num1 >> op >> num2;

        switch (op) {
            case '+':
                return std::to_string(num1 + num2);
            case '-':
                return std::to_string(num1 - num2);
            case '*':
                return std::to_string(num1 * num2);
            case '/':
                if (num2 != 0)
                    return std::to_string(num1 / num2);
                else
                    return "��������Ϊ��";
        }

        return "��Ч�Ĳ�����";
    }

    void showHelp(const std::string& topic = "") {
        if (topic.empty()) {
            std::cout << "�����ǿ��õ����" << std::endl;
            std::cout << "orint [value] : ��ӡ���������ֵ����ʽ�Ľ�����ַ���������" << std::endl;
            std::cout << "var [name] [value] : ���ñ���" << std::endl;
            std::cout << "list [name] : �������б�" << std::endl;
            std::cout << "loop [times] [code] : ִ��ѭ��" << std::endl;
            std::cout << "help [command] : ��ʾ�������ϸ��Ϣ" << std::endl;
        }
        else if (topic == "orint") {
            std::cout << "orint�������ڴ�ӡ���������ֵ����ʽ�Ľ�����ַ��������ݡ��÷���orint [value]" << std::endl;
            std::cout << "  value�����Ǳ���������$��ͷ������ʽ��֧�ּӼ��˳�����˫���Ű������ַ���" << std::endl;
        }
        else if (topic == "var") {
            std::cout << "var�����������ñ������÷���var [name] [value]" << std::endl;
        }
        else if (topic == "list") {
            std::cout << "list�������ڴ������б��÷���list [name]" << std::endl;
        }
        else if (topic == "loop") {
            std::cout << "loop��������ִ��ѭ�����÷���loop [times] [code]" << std::endl;
        }
        else if (topic == "help") {
            std::cout << "help����������ʾ�������ϸ��Ϣ���÷���help [command]" << std::endl;
        }
        else {
            std::cout << "δ֪���������⣬������\"help\"�鿴���п�������" << std::endl;
        }
    }
};

int main() {
    PothonInterpreter interpreter;

    interpreter.run();
	return 0;
}

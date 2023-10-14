
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
                    std::cout << "未知的变量：" << variableName << std::endl;
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
                std::cout << "无法识别的参数：" << value << std::endl;
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
                    return "除数不能为零";
        }

        return "无效的操作符";
    }

    void showHelp(const std::string& topic = "") {
        if (topic.empty()) {
            std::cout << "以下是可用的命令：" << std::endl;
            std::cout << "orint [value] : 打印输出变量的值、算式的结果或字符串的内容" << std::endl;
            std::cout << "var [name] [value] : 设置变量" << std::endl;
            std::cout << "list [name] : 创建空列表" << std::endl;
            std::cout << "loop [times] [code] : 执行循环" << std::endl;
            std::cout << "help [command] : 显示命令的详细信息" << std::endl;
        }
        else if (topic == "orint") {
            std::cout << "orint命令用于打印输出变量的值、算式的结果或字符串的内容。用法：orint [value]" << std::endl;
            std::cout << "  value可以是变量名（以$开头）、算式（支持加减乘除）或双引号包裹的字符串" << std::endl;
        }
        else if (topic == "var") {
            std::cout << "var命令用于设置变量。用法：var [name] [value]" << std::endl;
        }
        else if (topic == "list") {
            std::cout << "list命令用于创建空列表。用法：list [name]" << std::endl;
        }
        else if (topic == "loop") {
            std::cout << "loop命令用于执行循环。用法：loop [times] [code]" << std::endl;
        }
        else if (topic == "help") {
            std::cout << "help命令用于显示命令的详细信息。用法：help [command]" << std::endl;
        }
        else {
            std::cout << "未知的命令主题，请输入\"help\"查看所有可用命令" << std::endl;
        }
    }
};

int main() {
    PothonInterpreter interpreter;

    interpreter.run();
	return 0;
}

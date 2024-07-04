// CMakeProject1.cpp: определяет точку входа для приложения.
//

#include "CMakeProject1.h"
using namespace std;

//функция для разбивания строки на подстроки
void tokenize(const std::string& str, std::vector<std::string>& tokens, const std::string& delimiters = " ") // функция для разделения строки на подстроки разделения через пробел
{
    std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    std::string::size_type pos = str.find_first_of(delimiters, lastPos);
    while (std::string::npos != pos || std::string::npos != lastPos)
    {
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        lastPos = str.find_first_not_of(delimiters, pos);
        pos = str.find_first_of(delimiters, lastPos);
    }
}

//класс с элементами чека
class Element {
private:
    int num;
    int count;
    vector<string> kat;

public:
    Element(vector<string> strElem) {
        num = stoi(strElem[0]);
        count = stoi(strElem[1]);
        for (int i = 0; i < strElem.size() - 2; i++)
        {
            kat.push_back(strElem[i + 2]);
        }
    }
    int getnum() {
        return num;
    }
    int getcount() {
        return count;
    }
    string getkat() {
        return kat[0];
    }
    vector<string> getkatall() {
        return kat;
    }
};

//класс условий для скидки
class kitElements {
private:
    int count;
    string kat;
public:
    kitElements(vector<string> var) {
        count = stoi(var[0]);
        kat = var[1];
    }
    int getcount(){
        return count;
    }
    void subcount(int n) {
        count -= n;
    }
    string getkat() {
        return kat;
    }
};

//класс вспомогательный для дальнейшего вывода результата
class remaind {
private:
    vector<int> numbers;
    string kat;
public:
    remaind(string var) {
        kat = var;
    }
    void pull(int n) {
        numbers.push_back(n);
    }
    void print() {
        for (int i = 0; i<numbers.size()-1; i++) {
            cout << numbers[i] << ",";
        }
        cout << numbers[numbers.size() - 1];
        cout << " " << kat << "\n";
    }
};

//bool sort(vector<Element> Elem, vector<remaind> num, vector<kitElements> kits) {
//    vector<string> ElemKat = Elem[0].getkatall();
//    for (int i = 0; i < ElemKat.size(); i++) {
//        for (int k = 0; k < kits.size(); k++) {
//            if (kits[k].getkat() == ElemKat[i]) {
//                kits[k].subcount(Elem[0].getcount());
//                num[k].pull(Elem[0].getnum());
//                for (int i = 0; i < kits.size(); i++)
//                {
//                    if (kits[i].getcount() <= 0) {
//                        return true;
//                    }
//                    else
//                    {
//                        vector<Element> m = Elem.erase(Elem.cbegin());
//                        sort(m,num, kits);
//                    }
//                }
//            }
//        }
//    }
//}

int main()
{
    //объявление переменных
    ifstream doc("document.txt"),kit("kit.txt");
	setlocale(LC_ALL, "RUS");
    vector<Element> chekOneKat;
    vector<Element> chekMoreKat;
    vector<kitElements> kategoria;
    vector<string> strElement;
    vector<remaind> ListKat;
    string buffer;
    //проверка на наличие файла
    if (!doc.is_open()) {
        printf("файл 1 не найден");
        system("pause");
        exit;
    }
    if (!kit.is_open()) {
        printf("файл 2 не найден");
        system("pause");
        exit;
    }

    //посимвольное чтение kit
    do
    {
        char ch = kit.get();

       if (ch != '\n')
       {
           buffer += ch;

       }
       else
       {
           //если конец строки, то записываем новый элемент
           buffer += " ";
           tokenize(buffer, strElement);
           kategoria.push_back(kitElements(strElement));
           strElement.clear();
           buffer.clear();
       }

    } while (!kit.eof());
    buffer[buffer.size() - 1] = NULL;
    tokenize(buffer, strElement);
    //проверка на то последняя строка пустая или нет.(если строка из пробелов будет ошибка)
    if (strElement.size()>2){
        kategoria.push_back(kitElements(strElement));
    } 
    strElement.clear();
    buffer.clear();
    //конец посимвольного чтения файла kit
    //Посимвольное чтение файла doc
    do
    {
        char ch = doc.get();

        if (ch != '\n')
        {
            buffer += ch;

        }
        else
        {
            //если конец строки, то записываем новый элемент
            buffer += " ";
            tokenize(buffer, strElement);
            //пропускаем без элементы без категорий
            if(strElement.size()==3){
                chekOneKat.push_back(Element(strElement));
            }
            if (strElement.size() > 3) {
                chekMoreKat.push_back(Element(strElement));
            }

            strElement.clear();
            buffer.clear();
        }

    } while (!doc.eof());
    buffer[buffer.size() - 1] = NULL;
    tokenize(buffer, strElement);
    //проверка на то последняя строка пустая или нет.(если строка из пробелов будет ошибка)
    if (strElement.size() > 2) {
        chekOneKat.push_back(Element(strElement));
    }
    strElement.clear();
    buffer.clear();
    //конец посимвольного чтения файла doc
    
    //заполнение листа с категориями и какие элементы с одной категорией из чека в него вошли
    for (int i = 0; i < kategoria.size(); i++) {
        ListKat.push_back(remaind(kategoria[i].getkat()));
        for (int k = 0; k < chekOneKat.size(); k++) {
            if (kategoria[i].getkat() == chekOneKat[k].getkat()) {
                kategoria[i].subcount(chekOneKat[k].getcount());
                ListKat[i].pull(chekOneKat[k].getnum());
                if (kategoria[i].getcount() <=0) {
                   break;
                }
            }
        }
    }



    //делаем проверку что условия выполнены и есть все товары из списка
    bool fl = true;
    for (int i = 0; i < kategoria.size(); i++)
    {
        if (kategoria[i].getcount()>0) {
            cout << "Нет подходящих категорий";
            fl = false; break;
        }
    }
    //выводим результат
    if (fl) {
        for (int i = 0; i < ListKat.size(); i++)
        {
            ListKat[i].print();
        }
    }


    doc.close();
    kit.close();
	return 0;
}

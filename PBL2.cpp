#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <string>
#include "hashtable.h"
#include "block.h"
#include "blockhash.h"
#include "donhang.h"
#include "kho.h"
#include "route.h"
#include "truck.h"
#include"user.h"
#include "function.h"
#include <set>

void showWindow1(HashTable& hash, Truck* truckArr[], User acc);//màn hình đăng nhập
void showWindow2(HashTable& hash, Truck* truckArr[], User acc);//màn hình menu
void showWindow3(HashTable& hash, Truck* truckArr[], User acc);//Tìm đơn hàng
void showWindow4(HashTable& hash, Truck* truckArr[], User acc);//Nhập hàng
void showWindow5(HashTable& hash, Truck* truckArr[], User acc);//Xuất hàng
void showWindow6(HashTable& hash, Truck* truckArr[], User acc);//quản lý điểm dừng
void showNhapHang(HashTable& hash, Truck* truckArr[], User acc, string bks); //màn nhập hàng

class TextField {
public:
    TextField(float x, float y, float width, float height, sf::Font& font)
        : position(x, y), size(width, height), font(font), isFocused(false) {
        // Khởi tạo hình chữ nhật làm nền cho TextField
        box.setSize(size);
        box.setPosition(position);
        box.setFillColor(sf::Color(255, 255, 255));  // Màu nền trắng
        box.setOutlineColor(sf::Color(0, 0, 0));  // Màu viền đen
        box.setOutlineThickness(2);

        // Khởi tạo text với font và kiểu chữ
        text.setFont(font);
        text.setPosition(position.x + 5, position.y + 5);  // Căn lề 5px
        text.setFillColor(sf::Color::Black);  // Màu chữ đen
        text.setCharacterSize(24);  // Kích thước chữ
    }

    void handleInput(const sf::Event& event) {

        if (isFocused) {

            if (event.type == sf::Event::TextEntered) {

                if (event.text.unicode < 128) {

                    char enteredChar = static_cast<char>(event.text.unicode);

                    if (enteredChar == '\b' && text.getString().getSize() > 0) {

                        // Xóa ký tự nếu là phím backspace

                        std::string currentText = text.getString();

                        currentText.pop_back();

                        text.setString(currentText);

                    }

                    else {

                        // Thêm ký tự vào văn bản

                        text.setString(text.getString() + enteredChar);

                    }

                }

            }

        }

    }

    void handleMouse(const sf::Event& event) {
        
        if (event.type == sf::Event::MouseButtonPressed) {
            if (box.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                isFocused = true;  // Lấy focus khi click vào TextField
            }
            else {
                isFocused = false;  // Mất focus nếu click ra ngoài
            }
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(box);  // Vẽ hộp textfield
        window.draw(text);  // Vẽ văn bản
    }
    std::string getText() const {
        return text.getString();
    }

    void setText(const std::string& newText) {
        text.setString(newText);
    }
    
    void setPassword() {
        isPassword = true;
    }

private:
    sf::RectangleShape box;
    sf::Text text;
    sf::Vector2f position;
    sf::Vector2f size;
    sf::Font& font;
    bool isFocused;
    bool isPassword = false;
};

//login screen
void showWindow1(HashTable& hash, Truck* truckArr[], User acc) {
    sf::RenderWindow window(sf::VideoMode(400, 800), "login");
    sf::Font font, fonttille;
    font.loadFromFile("../data/Roboto-Regular.ttf");
    fonttille.loadFromFile("../data/Roboto-Bold.ttf");
    sf::RectangleShape background(sf::Vector2f(400.f, 800.f));
    background.setFillColor(sf::Color(6, 140, 40));

    sf::Text Logintitle("Login", fonttille, 50);
    Logintitle.setPosition(150, 200);
    Logintitle.setOutlineThickness(2);
    Logintitle.setOutlineColor(sf::Color::Black);
    Logintitle.setFillColor(sf::Color::White);

    //nhap user setup
    sf::Text userText("User name", font, 20); //label user
    userText.setFillColor(sf::Color::White);
    userText.setPosition(30, 320);
    TextField user(150, 300, 200, 50, font); //textfield user

    //nhap password setup
    sf::Text passText("Password", font, 20); //label pass
    passText.setFillColor(sf::Color::White);
    passText.setPosition(30, 410);
    TextField pass(150, 400, 200, 50, font); //text field pass
    pass.setPassword();
    // Button setup
    sf::RectangleShape button(sf::Vector2f(200, 50));
    button.setPosition(100, 500);
    button.setFillColor(sf::Color::Cyan);

    sf::Text buttonText("login", font, 20);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setPosition(175, 510);

    sf::Text tb("", font, 15);
    tb.setPosition(160, 460);
    tb.setFillColor(sf::Color::Black);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            user.handleInput(event);
            pass.handleInput(event);
            if (event.type == sf::Event::MouseButtonPressed) {
                
                user.handleMouse(event);
               
                
                pass.handleMouse(event);
               
                if (button.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    //gọi hàm check is_login.
                    string accout = user.getText();
                    string pw = pass.getText();
                    std::cout << accout << endl;
                    std::cout << pw;
                    int check = islogin(accout, pw);
                    if (check == 1) {
                        window.close();
                        showWindow2(hash, truckArr, acc);  // Open next window
                    }
                    else {
                        tb.setString("username or password is wrong");
                    }
                   
                }
            }
        }

        window.clear();
        window.draw(background);
        window.draw(Logintitle);
        user.draw(window);
        pass.draw(window);
        window.draw(userText);
        window.draw(passText);
        window.draw(button);
        window.draw(buttonText);
        window.draw(tb);
        window.display();
    }
}

void showWindow2(HashTable& hash, Truck* truckArr[], User acc) {
    sf::RenderWindow window(sf::VideoMode(400, 800), "Menu");
    sf::RectangleShape background(sf::Vector2f(400, 800));
    //background.setFillColor(sf::Color(104, 171, 121));
    background.setFillColor(sf::Color::White);
    sf::Font font, titleFont;
    font.loadFromFile("../data/Roboto-Regular.ttf");
    titleFont.loadFromFile("../data/Roboto-Bold.ttf");

    //menu
    sf::Text menu("Menu", titleFont, 50);
    menu.setOutlineThickness(2);
    menu.setOutlineColor(sf::Color::Black);
    menu.setFillColor(sf::Color(6, 140, 40));
    menu.setPosition(140, 60);

    //tim don hang
    sf::RectangleShape bSearch(sf::Vector2f(200, 50));
    bSearch.setFillColor(sf::Color(6, 140, 40));
    bSearch.setOutlineThickness(2);
    bSearch.setOutlineColor(sf::Color::Black);
    bSearch.setPosition(100, 200);
    sf::Text search("Search", font, 20);
    search.setFillColor(sf::Color::White);
    search.setPosition(160, 210);
    

    //nhập hàng
    sf::RectangleShape bNhap(sf::Vector2f(200, 50));
    bNhap.setFillColor(sf::Color(6, 140, 40));
    bNhap.setOutlineThickness(2);
    bNhap.setOutlineColor(sf::Color::Black);
    bNhap.setPosition(100, 300);
    sf::Text nhap("Import Goods", font, 20);
    nhap.setFillColor(sf::Color::White);
    nhap.setPosition(145, 310);

    //Xuất hàng
    sf::RectangleShape bXuat(sf::Vector2f(200, 50));
    bXuat.setFillColor(sf::Color(6, 140, 40));
    bXuat.setOutlineThickness(2);
    bXuat.setOutlineColor(sf::Color::Black);
    bXuat.setPosition(100, 400);
    sf::Text xuat("Export Goods", font, 20);
    xuat.setFillColor(sf::Color::White);
    xuat.setPosition(145, 410);

    //Quản lý tuyến xe
    sf::RectangleShape bRoute(sf::Vector2f(200, 40));
    bRoute.setFillColor(sf::Color(6, 140, 40));
    bRoute.setOutlineThickness(2);
    bRoute.setOutlineColor(sf::Color::Black);
    bRoute.setPosition(100, 500);
    sf::Text route("Route Manager", font, 20);
    route.setFillColor(sf::Color::White);
    route.setPosition(135, 510);
    

    //Exit
    sf::RectangleShape bExit(sf::Vector2f(200, 40));
    bExit.setFillColor(sf::Color(6, 140, 40));
    bExit.setOutlineThickness(2);
    bExit.setOutlineColor(sf::Color::Black);
    bExit.setPosition(100, 600);
    sf::Text exit("Exit", font, 20);
    exit.setFillColor(sf::Color::White);
    exit.setPosition(180, 610);


    

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (bSearch.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    //gọi hàm check is_login.
                    window.close();
                    showWindow3(hash, truckArr, acc);  // Open next window
                }
                if (bNhap.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    //gọi hàm check is_login.
                    window.close();
                    showWindow4(hash, truckArr, acc);  // Open next window
                }
                if (bXuat.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    //gọi hàm check is_login.
                    window.close();
                    showWindow5(hash, truckArr, acc);  // Open next window
                }
                if (bRoute.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    //gọi hàm check is_login.
                    window.close();
                    showWindow6(hash, truckArr, acc);  // Open next window
                }
                if (bExit.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    //gọi hàm check is_login.
                    window.close();
                }
            }
        }

        window.clear();
        window.draw(background);
        window.draw(menu);
        window.draw(bSearch);
        window.draw(search);
        window.draw(bNhap);
        window.draw(nhap);
        window.draw(bXuat);
        window.draw(xuat);
        window.draw(bRoute);
        window.draw(route);
        window.draw(bExit);
        window.draw(exit);
        window.display();
    }
}

void showWindow3(HashTable& hash, Truck* truckArr[], User acc) {
    sf::RenderWindow window(sf::VideoMode(400, 800), "Search");
    sf::RectangleShape background(sf::Vector2f(400, 800));
    background.setFillColor(sf::Color::White);
    sf::Font titleFont, font;
    font.loadFromFile("../data/Roboto-Regular.ttf");
    titleFont.loadFromFile("../data/Roboto-Bold.ttf");
    //title
    sf::Text searchTitle("Search", font, 60);
    searchTitle.setPosition(100, 100);
    searchTitle.setFillColor(sf::Color::White);
    searchTitle.setOutlineThickness(2);
    searchTitle.setOutlineColor(sf::Color::Black);

    //back button
    sf::RectangleShape bback(sf::Vector2f(400,50));
    bback.setPosition(0, 0);
    bback.setFillColor(sf::Color(104, 171, 121));
    
    //button text
    
    sf::Text back("<  Search", font, 20);
    back.setPosition(10, 10);


    TextField nhapMa(10, 200, 330, 50, font);

    //search button
    sf::RectangleShape bSearch(sf::Vector2f(40, 40));
    bSearch.setFillColor(sf::Color::White);
    bSearch.setOutlineThickness(2);
    bSearch.setOutlineColor(sf::Color::Black);
    bSearch.setPosition(350, 205);
    sf::Text search("o", font, 50);
    search.setFillColor(sf::Color::Black);
    search.setPosition(355, 190);

    //Text Area

    sf::RectangleShape area(sf::Vector2f(380, 480));
    area.setFillColor(sf::Color::White);
    area.setOutlineThickness(2);
    area.setOutlineColor(sf::Color::Black);
    area.setPosition(10, 280);

    sf::Text info;
    info.setFont(font);
    info.setCharacterSize(30);
    info.setFillColor(sf::Color::Black);
    info.setPosition(20, 300);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            nhapMa.handleInput(event);
            nhapMa.handleMouse(event);
            if (event.type == sf::Event::MouseButtonPressed) {
                if (back.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    window.close();
                    showWindow2(hash, truckArr, acc);
                }
                if (bSearch.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    string maDH = nhapMa.getText();
                    //string tmp = timDH(&hash, maDH);
                    if (maDH.empty()) {
                        info.setString("Nhap ma don hang");
                    }
                    else {
                        info.setString(timDH(&hash, maDH));
                    }

                    
                }
            }
        }

        window.clear();
        window.draw(background);
        window.draw(bback);
        window.draw(back);
        window.draw(searchTitle);
        nhapMa.draw(window);
        window.draw(bSearch);
        window.draw(search);
        window.draw(area);
        window.draw(info);
        window.display();
    }
}






void showWindow4(HashTable& hash, Truck* truckArr[], User acc) {
    sf::RenderWindow window(sf::VideoMode(400, 800), "Import Goods");
    sf::RectangleShape background(sf::Vector2f(400, 800));
    background.setFillColor(sf::Color::White);
    sf::Font titleFont, font;
    font.loadFromFile("../data/Roboto-Regular.ttf");
    titleFont.loadFromFile("../data/Roboto-Bold.ttf");
    //title
    sf::Text iptitle("< Import goods", font, 20);
    iptitle.setPosition(10, 10);
    iptitle.setFillColor(sf::Color::White);
    sf::RectangleShape bar(sf::Vector2f(400, 50));
    bar.setFillColor(sf::Color(6, 140, 40));

    TextField nhapBKS(10, 100, 380, 50, font);



    //tim xem
    sf::RectangleShape timxe(sf::Vector2f(400, 100));
    timxe.setFillColor(sf::Color::White);
    timxe.setPosition(0, 160);
    timxe.setOutlineThickness(1);
    timxe.setOutlineColor(sf::Color(4, 140, 40));
    sf::Text chonxe(">", font, 40);
    chonxe.setPosition(370, 180);
    chonxe.setFillColor(sf::Color(4, 140, 40));
    sf::Text bks("", font, 20);
    bks.setPosition(20, 195);
    bks.setFillColor(sf::Color(4, 140, 40));

    //den noi va nhap hang
    sf::RectangleShape popup(sf::Vector2f(300, 100));
    sf::RectangleShape popup2(sf::Vector2f(300, 50));
    popup.setPosition(50, 200);
    popup2.setPosition(popup.getPosition());
    popup.setOutlineThickness(2);
    popup2.setOutlineThickness(2);
    popup.setOutlineColor(sf::Color(4, 140, 40));
    popup2.setOutlineColor(sf::Color(4, 140, 40));

    sf::Text tpop("Check in", font, 30);
    sf::Text tpop2("Import", font, 30);
    tpop.setFillColor(sf::Color(4, 140, 40));
    tpop2.setFillColor(sf::Color(4, 140, 40));
    tpop.setPosition(popup.getPosition().x + 20, popup.getPosition().y + 5);
    tpop2.setPosition(popup.getPosition().x + 20, popup.getPosition().y + 55);


    sf::Text thongbao("", font, 30);
    thongbao.setPosition(100, 400);
    thongbao.setFillColor(sf::Color::Black);


    int checkTruck = 0;
    int isPop = 0;
    int iscoming = 0;
    string bienso;
    while (window.isOpen()) {
        sf::Event event;
;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (iptitle.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    window.close();
                    showWindow2(hash, truckArr, acc);
                }
            }
            nhapBKS.handleMouse(event);
            nhapBKS.handleInput(event);
            if (event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed) {
                
                if (event.key.code == sf::Keyboard::Enter) {
                    string bs = nhapBKS.getText();
                    int ist = isTruck(truckArr, nhapBKS.getText());
                    Truck tr = truck(truckArr, nhapBKS.getText());
                    std::cout << tr.getBKS() << endl;
                    if (ist == 1) {
                        checkTruck = 1;
                        bks.setString(tr.getBKS() + " | " + taiTrong(truckArr, nhapBKS.getText()));
                        bienso = bs;

                    }
                    

                }
                if (bks.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    isPop = 1;
                }
                if (tpop.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    coming(truckArr, acc);

                }
                if (tpop2.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    window.close();
                    //std::cout << ist + "-" << endl;
                    Truck tr = truck(truckArr, bienso);
                    cout << tr.getBKS() << endl;
                    showNhapHang(hash, truckArr, acc, bienso);
                }

            }


            window.clear();
                window.draw(background);
                window.draw(bar);
                window.draw(iptitle);
                nhapBKS.draw(window);

                if (checkTruck == 1) {
                    window.draw(timxe);
                    window.draw(chonxe);
                    window.draw(bks);

                }
            if (isPop == 1) {
                window.draw(popup);
                window.draw(popup2);
                window.draw(tpop);
                window.draw(tpop2);
            }
            if (iscoming == 1) {
                window.draw(thongbao);
            }



            window.display();
        }

    }
}

struct textWithBackground {
    sf::Text text;
    sf::RectangleShape background;
};
void showNhapHang(HashTable& hash, Truck* truckArr[], User acc, string bks) {
    sf::RenderWindow window(sf::VideoMode(400, 800), "Import Goods");
    sf::RectangleShape background(sf::Vector2f(400, 800));
    background.setFillColor(sf::Color::White);
    sf::Font titleFont, font;
    font.loadFromFile("../data/Roboto-Regular.ttf");
    titleFont.loadFromFile("../data/Roboto-Bold.ttf");
    //bar
    sf::RectangleShape bar(sf::Vector2f(400, 50));
    bar.setFillColor(sf::Color(4, 140, 40));
    sf::Text title("<  Import goods", font, 20);
    title.setFillColor(sf::Color::White);
    title.setPosition(10, 10);

    sf::Text chotDiem("Check out", font, 20);
    chotDiem.setFillColor(sf::Color::White);
    chotDiem.setPosition(300, 10);

    

    sf::Text donhang;
    donhang.setCharacterSize(20);
    donhang.setFillColor(sf::Color::Black);
    donhang.setFont(font);

    //list đơn hàng
    Truck tr = truck(truckArr, bks);
    string bs = tr.getBKS();
    std::cout << bs << endl;
    int soDH = tr.soDH();
    std::cout << soDH << endl;
    string* list = tr.dsMaDH(soDH);

    float y = 110.0f;
    sf::Text text("",font,20);
    text.setFillColor(sf::Color::Black);


    std::map<std::string, textWithBackground> items;
    for (int i = 0; i < soDH; i++) {
        std::cout << list[i] << endl;
        string txtString = "donhang" + std::to_string(i + 1);
        text.setString(list[i]);
        text.setPosition(20, y);
        sf::RectangleShape underText(sf::Vector2f(400, 40));
        underText.setFillColor(sf::Color::White);
        underText.setOutlineThickness(2);
        underText.setOutlineColor(sf::Color(4, 140, 40));
        underText.setPosition(0, y - 10);

        y += 40.0f;
        items[txtString] = { text, underText };

    }

    
    TextField nhapMaDH(10, 740, 380, 50, font);
    string select[20];
    int i = 0;

    sf::RectangleShape minibar(sf::Vector2f(400, 50));
    minibar.setPosition(0, 50);
    minibar.setFillColor(sf::Color(191, 191, 191));
    sf::Text DN("Da Nang", font, 20);
    DN.setFillColor(sf::Color::Black);
    DN.setPosition(minibar.getPosition().x + 20, minibar.getPosition().y + 15);
    sf::Text scan("Scaned " + to_string(i) + "/20", font, 20);
    scan.setFillColor(sf::Color::Black);
    scan.setPosition(minibar.getPosition().x + 200, minibar.getPosition().y + 15);
    sf::Text chot("import", font, 20);
    chot.setFillColor(sf::Color(4, 140, 40));
    chot.setPosition(minibar.getPosition().x + 325, minibar.getPosition().y + 15);
    sf::RectangleShape bchot(sf::Vector2f(70, 30));
    bchot.setFillColor(sf::Color(191,191,191));
    bchot.setOutlineThickness(1);
    bchot.setOutlineColor(sf::Color(4, 140, 40));
    bchot.setPosition(chot.getPosition().x - 5, chot.getPosition().y - 3);
    
    

    std::set<std::string> lightValue;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            nhapMaDH.handleInput(event);
            nhapMaDH.handleMouse(event);
            if (event.type == sf::Event::Closed) {//đóng cửa sổ khi click vào X
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (title.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {//bach trở lại màn hình trước.
                    window.close();
                    showWindow4(hash, truckArr, acc);
                }
                if (chotDiem.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    checkout(truckArr, bks);
                }
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                std::string inputValue = nhapMaDH.getText();
                //if(i == 20) error;

                int j = 0;
                for (j = 0; j < i; j++) {
                    if (select[j] == inputValue) {
                        //error
                        break;
                    }
                }
                bool found = false;
                // Kiểm tra xem giá trị đã đổi màu chưa
                    for (auto& item : items) {
                        if (item.second.text.getString() == nhapMaDH.getText()) {
                            found = true;
                            item.second.background.setFillColor(sf::Color(239, 245, 125));
                            /*item.second.text.setFillColor(sf::Color::White);*/
                            select[i + 1] = inputValue; // Thêm vào danh sách giá trị đã đổi màu
                            std::cout << select[i + 1] << endl;
                            i++;
                            break; // Thoát vòng lặp sau khi tìm thấy và đổi màu
                        }
                    }
                    if (found = false) {
                        std::cout << "khong dung" << endl;
                    }
                

                nhapMaDH.setText(""); // Reset chuỗi nhập sau khi xử lý
            }
            
        }





        window.clear();
        window.draw(background);
        window.draw(bar);
        window.draw(title);
        window.draw(chotDiem); 
        window.draw(minibar);
        window.draw(DN);
        window.draw(scan);
        window.draw(bchot);
        window.draw(chot);
        for (const auto& item : items) {
            const textWithBackground& element = item.second;
            window.draw(element.background); // Vẽ background trước
            window.draw(element.text);       // Vẽ text sau
        }
        nhapMaDH.draw(window);
        window.display();
    }   
}

void showWindow5(HashTable& hash, Truck* truckArr[], User acc) {

}
void showWindow6(HashTable& hash, Truck* truckArr[], User acc) {

}

//void showNhap(HashTable& hash, Truck* truckArr[], User acc) {
//    //khoi tao
//    sf::RenderWindow window(sf::VideoMode(400, 800), "Imports Good");
//    sf::RectangleShape background(sf::Vector2f(400, 800));
//    background.setFillColor(sf::Color::White);
//    sf::Font font, titleF;
//    font.loadFromFile("../data/Roboto-Regular.ttf");
//    titleF.loadFromFile("../data/Roboto-Bold.ttf");
//    sf::RectangleShape bar(sf::Vector2f(400, 50));
//    bar.setFillColor(sf::Color(4,140,40));
//    sf::Text titleT("< Nhap hang", font, 20);
//    titleT.setFillColor(sf::Color::White);
//    titleT.setPosition(10, 15);
//
//
//    TextField searchbar(10, 80, 380, 50, font);
//
//    sf::Text xe1("", font, 25);
//    xe1.setPosition(20, 200);
//    xe1.setFillColor(sf::Color(4, 140, 40));
//
//    sf::RectangleShape xe(sf::Vector2f(400, 2));
//    xe.setFillColor(sf::Color(163, 161, 155));
//    xe.setPosition(0, 240);
//
//    //notion
//    sf::RenderWindow mess(sf::VideoMode(200, 100), "mess", sf::Style::None);
//    sf::RectangleShape messtheme(sf::Vector2f(200, 100));
//    messtheme.setFillColor(sf::Color::White);
//
//    sf::RectangleShape line(sf::Vector2f(200, 2));
//    line.setFillColor(sf::Color(163, 161, 155));
//    line.setPosition(0, 100);
//    sf::Text mescheckin("Check in", font,20);
//    sf::Text mesimport("Import", font, 20);
//    mescheckin.setPosition(10, 10);
//    mesimport.setPosition(10, 60);
//
//
//
//
//    //thao tac & hien thi
//    while (window.isOpen()) {
//        sf::Event event;
//        bool isTr = false;
//        bool isPop = false;
//        //thao tac
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed) {
//                window.close();
//            }
//            searchbar.handleInput(event);
//            searchbar.handleMouse(event);
//
//            if (event.type == sf::Event::MouseButtonPressed) {
//                if (titleT.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
//                    window.clear();
//                    showWindow2(hash, truckArr, acc);
//                }
//                if (xe1.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
//                    isPop = true;
//                }
//            }
//            if (event.type == sf::Event::KeyPressed) {
//                if (event.key.code == sf::Keyboard::Enter) {
//                    string bks = searchbar.getText();
//                    isTr = isTruck(truckArr, bks);
//                    if (isTr) {
//                        Truck tr = truck(truckArr, bks);
//                        xe1.setString(bks);
//                    }
//                    else {
//                        xe1.setString("Nhap lai bks");
//                    }
//                    
//
//                }
//            }
//        }
//
//        
//
//
//
//
//        //hien thi
//        window.clear(); 
//        window.draw(background);
//        window.draw(bar);
//        window.draw(titleT);
//        searchbar.draw(window);
//        if (isTr) {
//            window.draw(xe1);
//            window.draw(xe);
//        }
//            
//        if (isPop) {
//            mess.setVisible(true);
//            isPop = false;
//        }
//        while (mess.isOpen()) {
//            sf::Event event;
//            while (mess.pollEvent(event)) {
//                if (event.type == sf::Event::Closed) {
//                    mess.setVisible(false);
//                }
//            }
//
//            mess.clear();
//            mess.draw(messtheme);
//            mess.draw(line);
//            mess.draw(mescheckin);
//            mess.draw(mesimport);
//            mess.display();
//        }
//        
//
//
//        window.display();
//    }
//
//
//
//
//
//}

int main() {
    HashTable* hash;
    Kho* khoArr[KHO_SIZE];
    Route* route[5];
    Truck* truckArr[TRUCK_SIZE];
    User acc("", "", "");
    
    // Call init to set up all components
    init(hash, khoArr, route, truckArr, acc);

    //showWindow1(*hash, truckArr, acc);
    showWindow1(*hash,truckArr,acc);
    return 0;
}


#include <SFML/Graphics.hpp>
#include "source.cpp"
#include "congty.h"
// #include "vanchuyen.h"
using namespace sf;

// nhap
bool nhap(string &bs, int key);
bool bks_check(Truck *truckArr[], int num, User user, string bs);
bool s_check(Kho *khoArr[], int num, string ma);
void search(Kho *khoArr[], int num);
void nhap_bks(Truck *truckArr[], int num, User user);

bool bks_hang(Truck *truckArr[], int num, User user, Kho *khoArr[], int n, string bs, int key);

// in-out DonHang
void in_out(Truck *truckArr[], int num, User user, Kho *khoArr[], int n, int key = 1);
void io_DonHang(Truck *truckArr[], int num, User user, Kho *khoArr[], int n, int key);
bool nhapHang_check(Kho *khoArr[], Truck *truck, User user, string ma, int n);
bool xuatHang_check(Kho *khoArr[], Truck *truck, User user, string ma, int n);
void xuatnhap_Hang(Truck *truck, User user, Kho *khoArr[], int n, int key);

RenderWindow window(VideoMode(800, 600), "PBL2 OOP");
Vector2u windowSize = window.getSize();
Sprite showbackground;
Font font;

float getButton_Position(float &button)
{
    button += 70;
    return button;
}

//      ******************main_GUI*****************
int GUI(Truck *truckArr[], Kho *khoArr[], User user)
{
    Image icon;
    Texture background;

    if (!font.loadFromFile("arial.ttf"))
        return -1;

    if (!icon.loadFromFile("icon.jfif"))
        return -1;

    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    if (!background.loadFromFile("icon.jfif"))
        return -1;

    showbackground.setTexture(background);

    // fix ảnh nền vừa với cửa sổ
    Vector2u textureSize = background.getSize();
    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
    showbackground.setScale(scaleX, scaleY);

    // create dialog_Main
    RectangleShape dialogBox(Vector2f(windowSize.x * 0.5f, windowSize.y * 0.07f));
    dialogBox.setFillColor(Color(200, 200, 200));
    dialogBox.setOutlineThickness(2);
    dialogBox.setOutlineColor(Color::Black);
    dialogBox.setPosition(windowSize.x * 0.25f, windowSize.y * 0.03f);

    Text dialogText("LOGISTIC WAREHOUSE MANAGEMENT", font, 20);
    dialogText.setFillColor(Color::Blue);
    dialogText.setPosition(dialogBox.getPosition().x + 10, dialogBox.getPosition().y + 5);

    // Nút và text của nút
    float buttonY = windowSize.y * 0.3f;
    float buttonWidth = windowSize.x * 0.3f;
    float buttonHeight = windowSize.y * 0.07f;

    RectangleShape outputButton(Vector2f(buttonWidth, buttonHeight));
    outputButton.setFillColor(Color(204, 199, 186));
    outputButton.setPosition((windowSize.x - buttonWidth) / 2, buttonY);

    Text outputText("OUTPUT PRODUCT", font, 20);
    outputText.setFillColor(Color(14, 64, 71));
    outputText.setPosition(outputButton.getPosition().x + 25, outputButton.getPosition().y + 5);

    RectangleShape inputButton(Vector2f(buttonWidth, buttonHeight));
    inputButton.setFillColor(Color(204, 199, 186));
    inputButton.setPosition((windowSize.x - buttonWidth) / 2, getButton_Position(buttonY));

    Text inputText("INPUT PRODUCT", font, 20);
    inputText.setFillColor(Color(14, 64, 71));
    inputText.setPosition(inputButton.getPosition().x + 25, inputButton.getPosition().y + 5);

    RectangleShape searchButton(Vector2f(buttonWidth, buttonHeight));
    searchButton.setFillColor(Color(204, 199, 186));
    searchButton.setPosition((windowSize.x - buttonWidth) / 2, getButton_Position(buttonY));

    Text searchText("SEARCH PRODUCT", font, 20);
    searchText.setFillColor(Color(14, 64, 71));
    searchText.setPosition(searchButton.getPosition().x + 25, searchButton.getPosition().y + 5);

    RectangleShape exitButton(Vector2f(buttonWidth, buttonHeight));
    exitButton.setFillColor(Color(204, 199, 186));
    exitButton.setPosition((windowSize.x - buttonWidth) / 2, getButton_Position(buttonY));

    Text exitText("EXIT", font, 20);
    exitText.setFillColor(Color(14, 64, 71));
    exitText.setPosition(exitButton.getPosition().x + 75, exitButton.getPosition().y + 5);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
            if (event.type == Event::Closed)
                window.close();
            else if (event.type == Event::MouseButtonPressed)
            {
                Vector2i msPos = Mouse::getPosition(window);
                if (outputButton.getGlobalBounds().contains(static_cast<Vector2f>(msPos)))
                    in_out(truckArr, TOTAL_TRUCKS, user, khoArr, TOTAL_WAREHOUSES, 0);
                else if (inputButton.getGlobalBounds().contains(static_cast<Vector2f>(msPos)))
                    in_out(truckArr, TOTAL_TRUCKS, user, khoArr, TOTAL_WAREHOUSES);
                else if (searchButton.getGlobalBounds().contains(static_cast<Vector2f>(msPos)))
                    search(khoArr, 2);
                else if (exitButton.getGlobalBounds().contains(static_cast<Vector2f>(msPos)))
                    window.close();
            }

        window.clear();
        window.draw(showbackground);
        window.draw(dialogBox);
        window.draw(dialogText);
        window.draw(inputButton);
        window.draw(inputText);
        window.draw(outputButton);
        window.draw(outputText);
        window.draw(searchButton);
        window.draw(searchText);
        window.draw(exitButton);
        window.draw(exitText);
        window.display();
    }
    return 0;
}

// search = nhap + s_check
void search(Kho *khoArr[], int num)
{
    bool continueInput = true;
    while (window.isOpen() && continueInput)
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
                return;
            }
            string ma;

            if (nhap(ma, 1))
            {
                if (s_check(khoArr, num, ma))
                    continue;
                continueInput = false;
            }
            else
                continueInput = false;
        }
    }
}

void in_out(Truck *truckArr[], int num, User user, Kho *khoArr[], int n, int key)
{
    RectangleShape dialogBox(Vector2f(windowSize.x * 0.23f, windowSize.y * 0.07f));
    dialogBox.setFillColor(Color(200, 200, 200));
    dialogBox.setOutlineThickness(2);
    dialogBox.setOutlineColor(Color::Black);
    dialogBox.setPosition(windowSize.x * 0.38f, windowSize.y * 0.03f);

    Text dialogText("INPUT PRODUCT", font, 20);
    dialogText.setFillColor(Color::Blue);
    dialogText.setPosition(dialogBox.getPosition().x + 10, dialogBox.getPosition().y + 5);

    float buttonY = windowSize.y * 0.3f;
    float buttonWidth = windowSize.x * 0.3f;
    float buttonHeight = windowSize.y * 0.07f;

    RectangleShape outputButton(Vector2f(buttonWidth, buttonHeight));
    outputButton.setFillColor(Color(204, 199, 186));
    outputButton.setPosition((windowSize.x - buttonWidth) / 2, buttonY);

    Text outputText("CAP NHAT XE DA DEN", font, 20);
    outputText.setFillColor(Color(14, 64, 71));
    outputText.setPosition(outputButton.getPosition().x + 25, outputButton.getPosition().y + 5);

    RectangleShape inputButton(Vector2f(buttonWidth, buttonHeight));
    inputButton.setFillColor(Color(204, 199, 186));
    inputButton.setPosition((windowSize.x - buttonWidth) / 2, buttonY + buttonHeight + 10);

    Text inputText("NHAP HANG", font, 20);
    inputText.setFillColor(Color(14, 64, 71));
    inputText.setPosition(inputButton.getPosition().x + 25, inputButton.getPosition().y + 5);

    RectangleShape exitButton(Vector2f(buttonWidth, buttonHeight));
    exitButton.setFillColor(Color(204, 199, 186));
    exitButton.setPosition((windowSize.x - buttonWidth) / 2, buttonY + 2 * (buttonHeight + 10));

    Text exitText("EXIT", font, 20);
    exitText.setFillColor(Color(14, 64, 71));
    exitText.setPosition(exitButton.getPosition().x + 75, exitButton.getPosition().y + 5);

    if (!key)
    {
        inputText.setString("XUAT HANG");
        dialogText.setString("OUTPUT PRODUCT");
        dialogBox.setSize(Vector2f(windowSize.x * 0.27f, windowSize.y * 0.07f));
        dialogBox.setPosition(windowSize.x * 0.37f, windowSize.y * 0.03f);
    }

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            else if (event.type == Event::MouseButtonPressed)
            {
                Vector2i mPos;
                mPos = Mouse::getPosition(window);
                if (outputButton.getGlobalBounds().contains(static_cast<Vector2f>(mPos)))
                {
                    nhap_bks(truckArr, num, user);
                }
                else if (inputButton.getGlobalBounds().contains(static_cast<Vector2f>(mPos)))
                {
                    io_DonHang(truckArr, num, user, khoArr, n, key);
                }
                else if (exitButton.getGlobalBounds().contains(static_cast<Vector2f>(mPos)))
                {
                    return;
                }
            }
        }

        window.clear();
        window.draw(showbackground);

        window.draw(dialogBox);
        window.draw(dialogText);
        window.draw(outputButton);
        window.draw(outputText);
        window.draw(inputButton);
        window.draw(inputText);
        window.draw(exitButton);
        window.draw(exitText);
        window.display();
    }
}

/*-------------------------------------------SEARCH--------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------*/
//
/*            */
// io_DonHang, nhap_bks, xuatnhap_Hang, search ma = 1, xe = 0
bool nhap(string &bs, int key)
{
    Text promptText;

    if (key)
        promptText.setString("Nhap ma don hang:");
    else
        promptText.setString("Nhap BKS:");

    promptText.setFont(font);
    promptText.setCharacterSize(20);
    promptText.setFillColor(Color::Black);
    promptText.setPosition(200, 120);

    Text inputText("", font, 20);
    inputText.setFillColor(Color::Black);
    inputText.setPosition(205, 190);

    RectangleShape inputBox(Vector2f(400, 50));
    inputBox.setFillColor(Color::White);
    inputBox.setOutlineThickness(2);
    inputBox.setOutlineColor(Color::Black);
    inputBox.setPosition(200, 180);

    RectangleShape okButton(Vector2f(85, 40));
    okButton.setFillColor(Color(204, 199, 186));
    okButton.setPosition(250, 270);

    Text okText("OK", font, 20);
    okText.setFillColor(Color::Blue);
    okText.setPosition(270, 275);

    RectangleShape exitButton(Vector2f(130, 40));
    exitButton.setFillColor(Color(204, 199, 186));
    exitButton.setPosition(385, 270);

    Text exitText("Cancel", font, 20);
    exitText.setFillColor(Color::Blue);
    exitText.setPosition(420, 275);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::TextEntered)
            {
                if (event.text.unicode == '\b' && !bs.empty())
                    bs.pop_back();
                else if (event.text.unicode < 128 && event.text.unicode != '\b')
                    bs += static_cast<char>(event.text.unicode);
                inputText.setString(bs);
            }

            if (event.type == Event::MouseButtonPressed)
            {
                Vector2i mousePos = Mouse::getPosition(window);
                if (okButton.getGlobalBounds().contains(static_cast<Vector2f>(mousePos)))
                    return true;
                else if (exitButton.getGlobalBounds().contains(static_cast<Vector2f>(mousePos)))
                    return false;
            }

            if (Keyboard::isKeyPressed(Keyboard::Enter))
                if (bs != "")
                    return true;
        }

        window.clear();
        window.draw(showbackground);
        window.draw(promptText);
        window.draw(inputBox);
        window.draw(inputText);
        window.draw(okButton);
        window.draw(okText);
        window.draw(exitButton);
        window.draw(exitText);
        window.display();
    }
}

bool s_check(Kho *khoArr[], int num, string ma)
{
    Text resultText("", font, 20);
    resultText.setFillColor(Color::Red);
    resultText.setPosition(220, 250);

    RectangleShape messageBox(Vector2f(400, 150));
    messageBox.setFillColor(Color(220, 220, 220));
    messageBox.setOutlineThickness(2);
    messageBox.setOutlineColor(Color::Black);
    messageBox.setPosition(200, 250);

    RectangleShape okButton(Vector2f(100, 40));
    okButton.setFillColor(Color(204, 199, 186));

    Text okText("Continue", font, 20);
    okText.setFillColor(Color::Blue);

    RectangleShape exitButton(Vector2f(80, 40));
    exitButton.setFillColor(Color(204, 199, 186));

    Text exitText("Exit", font, 20);
    exitText.setFillColor(Color::Blue);
    DonHang *DH = NULL;

    for (int i = 0; i < num; i++)
    {
        DH = khoArr[i]->searchDH(ma);
        if (DH)
        {
            resultText.setPosition(250, 260);
            okText.setPosition(300, 400);
            okButton.setPosition(290, 395);
            exitText.setPosition(450, 400);
            exitButton.setPosition(430, 395);
            messageBox.setSize(Vector2f(400, 200));
            // resultText.setString("Don hang da tim thay:");
            resultText.setPosition(320, 260);
            DH->showInfo(resultText);
            break;
        }
    }
    if (!DH)
    {
        okButton.setPosition(290, 350);
        okText.setPosition(300, 355);
        exitText.setPosition(450, 355);
        exitButton.setPosition(430, 350);
        resultText.setString("Khong tim thay thong tin don hang.");
        messageBox.setSize(Vector2f(400, 150));
        resultText.setPosition(235, 280);
    }

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed)
            {
                Vector2i mousePos = Mouse::getPosition(window);
                if (okButton.getGlobalBounds().contains(static_cast<Vector2f>(mousePos)))
                    return true;
                else if (exitButton.getGlobalBounds().contains(static_cast<Vector2f>(mousePos)))
                    return false;
            }
            Event waitEvent;
            while (window.pollEvent(waitEvent))
            {
                if (Keyboard::isKeyPressed(Keyboard::Enter))
                    return true;
            }
        }

        window.clear();
        window.draw(showbackground);
        window.draw(messageBox);
        window.draw(resultText);
        window.draw(okButton);
        window.draw(okText);
        window.draw(exitButton);
        window.draw(exitText);
        window.display();
    }
}

bool bks_check(Truck *truckArr[], int num, User user, string bs)
{
    Text resultText("", font, 20);
    resultText.setFillColor(Color::Red);
    resultText.setPosition(220, 250);

    RectangleShape messageBox(Vector2f(400, 150));
    messageBox.setFillColor(Color(220, 220, 220));
    messageBox.setOutlineThickness(2);
    messageBox.setOutlineColor(Color::Black);
    messageBox.setPosition(200, 250);

    RectangleShape okButton(Vector2f(100, 40));
    okButton.setFillColor(Color(204, 199, 186));

    Text okText("Continue", font, 20);
    okText.setFillColor(Color::Blue);

    RectangleShape exitButton(Vector2f(80, 40));
    exitButton.setFillColor(Color(204, 199, 186));

    Text exitText("Exit", font, 20);
    exitText.setFillColor(Color::Blue);

    okButton.setPosition(290, 350);
    okText.setPosition(300, 355);
    exitText.setPosition(450, 355);
    exitButton.setPosition(430, 350);
    messageBox.setSize(Vector2f(400, 150));
    resultText.setPosition(235, 280);

    int i = 0;

    for (i = 0; i < num; i++)
    {

        if (nv.getMa == bs)
        {
            truckArr[i]->setStatus(1);
            if (truckArr[i]->getKhoHT() != user.getKhoLamViec())
            {
                string tmp;
                tmp = truckArr[i]->getKhoHT();
                truckArr[i]->setKhoHT(user.getKhoLamViec());
                truckArr[i]->setKhoDen(tmp);
            }
            resultText.setString("Cap nhat xe " + bs + " thanh cong!");
            break;
        }
    }

    if (i == num)
    {
        resultText.setString("Khong ton tai xe " + bs);
        resultText.setPosition(300, 280);
    }

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed)
            {
                Vector2i mousePos = Mouse::getPosition(window);
                if (okButton.getGlobalBounds().contains(static_cast<Vector2f>(mousePos)))
                    return true;
                else if (exitButton.getGlobalBounds().contains(static_cast<Vector2f>(mousePos)))
                    return false;
            }
            Event waitEvent;
            while (window.pollEvent(waitEvent))
            {
                if (Keyboard::isKeyPressed(Keyboard::Enter))
                    return true;
            }
        }

        window.clear();
        window.draw(showbackground);
        window.draw(messageBox);
        window.draw(resultText);
        window.draw(okButton);
        window.draw(okText);
        window.draw(exitButton);
        window.draw(exitText);
        window.display();
    }
}

// nhap_bks = nhap + bks_check
void nhap_bks(Truck *truckArr[], int num, User user)
{
    bool continueInput = true;
    while (window.isOpen() && continueInput)
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
                return;
            }
            string bs;

            if (nhap(bs, 0))
            {
                if (bks_check(truckArr, num, user, bs))
                    continue;
                continueInput = false;
            }
            else
                continueInput = false;
        }
    }
}

/*--------------------------------NHAP_XUAT HANG-----------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------*/
//
// io_DonHang = bks_nhap + bks_hang
void io_DonHang(Truck *truckArr[], int num, User user, Kho *khoArr[], int n, int key)
{
    bool continueInput = true;
    while (window.isOpen() && continueInput)
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
                return;
            }
            string bs;

            if (nhap(bs, 0))
            {
                if (bks_hang(truckArr, num, user, khoArr, n, bs, key))
                    continue;
                continueInput = false;
            }
            else
                continueInput = false;
        }
    }
}

// bks_hang += xuatnhap_Hang
bool bks_hang(CongTy A, NhanVien nv, string bs, int key)
{
    Text resultText("", font, 20);
    resultText.setFillColor(Color::Red);
    resultText.setPosition(220, 250);

    RectangleShape messageBox(Vector2f(400, 150));
    messageBox.setFillColor(Color(220, 220, 220));
    messageBox.setOutlineThickness(2);
    messageBox.setOutlineColor(Color::Black);
    messageBox.setPosition(200, 250);

    RectangleShape okButton(Vector2f(100, 40));
    okButton.setFillColor(Color(204, 199, 186));

    Text okText("Continue", font, 20);
    okText.setFillColor(Color::Blue);

    RectangleShape exitButton(Vector2f(80, 40));
    exitButton.setFillColor(Color(204, 199, 186));

    Text exitText("Exit", font, 20);
    exitText.setFillColor(Color::Blue);

    okButton.setPosition(290, 350);
    okText.setPosition(300, 355);
    exitText.setPosition(450, 355);
    exitButton.setPosition(430, 350);
    messageBox.setSize(Vector2f(400, 150));
    resultText.setPosition(235, 280);

    if (A.getXe().find(bs))
    {
        if(A.getTuyen().getKho().find(nv.getKho())){

        }
    }
    else
    {
        resultText.setString("Khong ton tai xe " + bs);
        resultText.setPosition(300, 280);
    }
    Truck *truck = NULL;
    int i = 0;
    for (i = 0; i < A.getSoXe(); i++)
        if (truckArr[i]->getBKS() == bs)
        {
            truck = truckArr[i];
            break;
        }

    if (truck == NULL)

        else if (truck->getStatus() == 0)
        {
            resultText.setString("Xe " + bs + " van chua den!");
            resultText.setPosition(300, 280);
        }
    else
    {
        xuatnhap_Hang(truckArr[i], user, khoArr, n, key);
        return true;
    }

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed)
            {
                Vector2i mousePos = Mouse::getPosition(window);
                if (okButton.getGlobalBounds().contains(static_cast<Vector2f>(mousePos)))
                    return true;
                else if (exitButton.getGlobalBounds().contains(static_cast<Vector2f>(mousePos)))
                    return false;
            }
            Event waitEvent;
            while (window.pollEvent(waitEvent))
            {
                if (Keyboard::isKeyPressed(Keyboard::Enter))
                    return true;
            }
        }

        window.clear();
        window.draw(showbackground);
        window.draw(messageBox);
        window.draw(resultText);
        window.draw(okButton);
        window.draw(okText);
        window.draw(exitButton);
        window.draw(exitText);
        window.display();
    }
}

// nhapHang = 1, xuatHang = 0
//  xuatnhap_Hang = nhap + xuat/nhap_Hang_check
void xuatnhap_Hang(Truck *truck, User user, Kho *khoArr[], int n, int key)
{
    truck->danhSach();
    bool continueInput = true;
    while (window.isOpen() && continueInput)
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
                return;
            }
            string ma;

            if (nhap(ma, 1))
            {
                if (key)
                {
                    if (nhapHang_check(khoArr, truck, user, ma, n))
                        continue;
                }
                else
                {
                    if (xuatHang_check(khoArr, truck, user, ma, n))
                        continue;
                }
                continueInput = false;
            }
            else
                continueInput = false;
        }
    }
}

bool nhapHang_check(Kho *khoArr[], Truck *truck, User user, string ma, int n)
{
    Text resultText("", font, 20);
    resultText.setFillColor(Color::Red);
    resultText.setPosition(220, 250);

    RectangleShape messageBox(Vector2f(400, 150));
    messageBox.setFillColor(Color(220, 220, 220));
    messageBox.setOutlineThickness(2);
    messageBox.setOutlineColor(Color::Black);
    messageBox.setPosition(200, 250);

    RectangleShape okButton(Vector2f(100, 40));
    okButton.setFillColor(Color(204, 199, 186));

    Text okText("Continue", font, 20);
    okText.setFillColor(Color::Blue);

    RectangleShape exitButton(Vector2f(80, 40));
    exitButton.setFillColor(Color(204, 199, 186));

    Text exitText("Exit", font, 20);
    exitText.setFillColor(Color::Blue);

    okButton.setPosition(290, 350);
    okText.setPosition(300, 355);
    exitText.setPosition(450, 355);
    exitButton.setPosition(430, 350);
    messageBox.setSize(Vector2f(400, 150));
    resultText.setPosition(235, 280);

    DonHang *ord = truck->DH.find(ma);
    if (ord == NULL)
        resultText.setString("Khong co don hang " + ma + " tren xe!");
    else
    {
        string khoName = user.getKhoLamViec();
        Kho *kho = NULL;
        for (int i = 0; i < n; i++)
            if (khoArr[i]->getName() == khoName)
            {
                kho = khoArr[i];
                break;
            }

        if (kho)
        {
            truck->xuongTai(*ord, *kho);
            truck->setStatus(0);
            resultText.setString("Da nhap don hang " + ma);
            resultText.setPosition(300, 280);

            okText.setString("Add more");
            exitText.setString("Done");
        }
    }

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed)
            {
                Vector2i mousePos = Mouse::getPosition(window);
                if (okButton.getGlobalBounds().contains(static_cast<Vector2f>(mousePos)))
                    return true;
                else if (exitButton.getGlobalBounds().contains(static_cast<Vector2f>(mousePos)))
                    return false;
            }
            Event waitEvent;
            while (window.pollEvent(waitEvent))
            {
                if (Keyboard::isKeyPressed(Keyboard::Enter))
                    return true;
            }
        }

        window.clear();
        window.draw(showbackground);
        window.draw(messageBox);
        window.draw(resultText);
        window.draw(okButton);
        window.draw(okText);
        window.draw(exitButton);
        window.draw(exitText);
        window.display();
    }
}

bool xuatHang_check(Kho *khoArr[], Truck *truck, User user, string ma, int n)
{
    Text resultText("", font, 20);
    resultText.setFillColor(Color::Red);
    resultText.setPosition(220, 250);

    RectangleShape messageBox(Vector2f(400, 150));
    messageBox.setFillColor(Color(220, 220, 220));
    messageBox.setOutlineThickness(2);
    messageBox.setOutlineColor(Color::Black);
    messageBox.setPosition(200, 250);

    RectangleShape okButton(Vector2f(100, 40));
    okButton.setFillColor(Color(204, 199, 186));

    Text okText("Continue", font, 20);
    okText.setFillColor(Color::Blue);

    RectangleShape exitButton(Vector2f(80, 40));
    exitButton.setFillColor(Color(204, 199, 186));

    Text exitText("Exit", font, 20);
    exitText.setFillColor(Color::Blue);

    okButton.setPosition(290, 350);
    okText.setPosition(300, 355);
    exitText.setPosition(450, 355);
    exitButton.setPosition(430, 350);
    messageBox.setSize(Vector2f(400, 150));
    resultText.setPosition(235, 280);

    string khoDen = truck->getKhoDen();
    Kho *kho = NULL;

    // show ten block va danh sach don hang trong block
    for (int j = 0; j < n; j++)
        if (khoArr[j]->getName() == khoDen)
        {
            kho = khoArr[j];
            kho->showBlock(khoDen);
            break;
        }

    if (kho)
    {
        Block *block = (Block *)kho->blocks.find(khoDen);
        if (block)
        {
            DonHang *ord = block->find(ma);
            if (ord)
            {
                truck->lenTai(*ord, *block);
                truck->setStatus(0);
                resultText.setString("Da xuat don hang " + ma);
                resultText.setPosition(300, 280);
                okText.setString("Add more");
                exitText.setString("Done");
            }
            else
                resultText.setString("Khong co don hang " + ma + " trong kho!");
        }
        else
            resultText.setString("Khong ton tai block trong kho!");
    }
    else
        resultText.setString("Khong ton tai kho den!");

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed)
            {
                Vector2i mousePos = Mouse::getPosition(window);
                if (okButton.getGlobalBounds().contains(static_cast<Vector2f>(mousePos)))
                    return true;
                else if (exitButton.getGlobalBounds().contains(static_cast<Vector2f>(mousePos)))
                    return false;
            }
            Event waitEvent;
            while (window.pollEvent(waitEvent))
            {
                if (Keyboard::isKeyPressed(Keyboard::Enter))
                    return true;
            }
        }

        window.clear();
        window.draw(showbackground);
        window.draw(messageBox);
        window.draw(resultText);
        window.draw(okButton);
        window.draw(okText);
        window.draw(exitButton);
        window.draw(exitText);
        window.display();
    }
}

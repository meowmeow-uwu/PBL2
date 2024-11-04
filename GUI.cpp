#include <iostream>
#include <SFML/Graphics.hpp>
#include "source.cpp"
using namespace std;

void input();
void output();
void search();

sf::RenderWindow window(sf::VideoMode(800, 600), "PBL2 OOP");
sf::Vector2i mPos;
sf::Vector2u windowSize = window.getSize();
sf::Font font;

bool isVisible = true;

float getButton_Position(float &button)
{
  button += 70;
  return button;
}

int main()
{
  // create window
  sf::Image icon;
  if (!icon.loadFromFile("icon.jfif"))
  {
    return -1;
  }
  window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

  // set Background
  sf::Texture background;
  if (!background.loadFromFile("icon.jfif"))
  {
    return -1;
  }

  sf::Sprite showbackground;
  showbackground.setTexture(background);

  // fix ảnh nền vừa với cửa sổ
  sf::Vector2u textureSize = background.getSize();

  float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
  float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
  showbackground.setScale(scaleX, scaleY);

  // create dialog_Main
  if (!font.loadFromFile("arial.ttf"))
  {
    return -1;
  }

  sf::RectangleShape dialogBox(sf::Vector2f(windowSize.x * 0.5f, windowSize.y * 0.07f));
  dialogBox.setFillColor(sf::Color(200, 200, 200));
  dialogBox.setOutlineThickness(2);
  dialogBox.setOutlineColor(sf::Color::Black);
  dialogBox.setPosition(windowSize.x * 0.25f, windowSize.y * 0.03f);

  sf::Text dialogText("LOGISTIC WAREHOUSE MANAGEMENT", font, 20);
  dialogText.setFillColor(sf::Color::Blue);
  dialogText.setPosition(dialogBox.getPosition().x + 10, dialogBox.getPosition().y + 5);

  // Nút và text của nút
  float buttonY = windowSize.y * 0.3f;
  float buttonWidth = windowSize.x * 0.3f;
  float buttonHeight = windowSize.y * 0.07f;

  sf::RectangleShape outputButton(sf::Vector2f(buttonWidth, buttonHeight));
  outputButton.setFillColor(sf::Color(204, 199, 186));
  outputButton.setPosition((windowSize.x - buttonWidth) / 2, buttonY);

  sf::Text outputText("OUTPUT PRODUCT", font, 20);
  outputText.setFillColor(sf::Color(14, 64, 71));
  outputText.setPosition(outputButton.getPosition().x + 25, outputButton.getPosition().y + 5);

  sf::RectangleShape inputButton(sf::Vector2f(buttonWidth, buttonHeight));
  inputButton.setFillColor(sf::Color(204, 199, 186));
  inputButton.setPosition((windowSize.x - buttonWidth) / 2, getButton_Position(buttonY));

  sf::Text inputText("INPUT PRODUCT", font, 20);
  inputText.setFillColor(sf::Color(14, 64, 71));
  inputText.setPosition(inputButton.getPosition().x + 25, inputButton.getPosition().y + 5);

  sf::RectangleShape searchButton(sf::Vector2f(buttonWidth, buttonHeight));
  searchButton.setFillColor(sf::Color(204, 199, 186));
  searchButton.setPosition((windowSize.x - buttonWidth) / 2, getButton_Position(buttonY));

  sf::Text searchText("SEARCH PRODUCT", font, 20);
  searchText.setFillColor(sf::Color(14, 64, 71));
  searchText.setPosition(searchButton.getPosition().x + 25, searchButton.getPosition().y + 5);

  sf::RectangleShape exitButton(sf::Vector2f(buttonWidth, buttonHeight));
  exitButton.setFillColor(sf::Color(204, 199, 186));
  exitButton.setPosition((windowSize.x - buttonWidth) / 2, getButton_Position(buttonY));

  sf::Text exitText("EXIT", font, 20);
  exitText.setFillColor(sf::Color(14, 64, 71));
  exitText.setPosition(exitButton.getPosition().x + 75, exitButton.getPosition().y + 5);

  // phiên làm việc màn hình chính
  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
      if (event.type == sf::Event::Closed)
        window.close();

    window.clear();
    window.draw(showbackground);
    if (event.type == sf::Event::MouseButtonPressed)
    {
      mPos = sf::Mouse::getPosition(window);

      if (outputButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mPos)))
      {
        isVisible = false;
        output();
      }
      else if (inputButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mPos)))
      {
        isVisible = false;
        input();
      }
      else if (searchButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mPos)))
      {
        isVisible = false;
        search();
      }
      else if (exitButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mPos)))
      {
        window.close();
      }
    }
    if (isVisible)
    {
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
    }
    else
      window.display();
  }
  return 0;
}

void input()
{
  if (!font.loadFromFile("arial.ttf"))
  {
    return;
  }
  sf::RectangleShape dialogBox(sf::Vector2f(windowSize.x * 0.5f, windowSize.y * 0.07f));
  dialogBox.setFillColor(sf::Color(200, 200, 200));
  dialogBox.setOutlineThickness(2);
  dialogBox.setOutlineColor(sf::Color::Black);
  dialogBox.setPosition(windowSize.x * 0.25f, windowSize.y * 0.03f);

  sf::Text dialogText("INPUT PRODUCT", font, 20);
  dialogText.setFillColor(sf::Color::Blue);
  dialogText.setPosition(dialogBox.getPosition().x + 10, dialogBox.getPosition().y + 5);

  // Nút và text của nút
  float buttonY = windowSize.y * 0.3f;
  float buttonWidth = windowSize.x * 0.3f;
  float buttonHeight = windowSize.y * 0.07f;

  sf::RectangleShape outputButton(sf::Vector2f(buttonWidth, buttonHeight));
  outputButton.setFillColor(sf::Color(204, 199, 186));
  outputButton.setPosition((windowSize.x - buttonWidth) / 2, buttonY);

  sf::Text outputText("CAP NHAT XE DA DEN", font, 20);
  outputText.setFillColor(sf::Color(14, 64, 71));
  outputText.setPosition(outputButton.getPosition().x + 25, outputButton.getPosition().y + 5);

  sf::RectangleShape inputButton(sf::Vector2f(buttonWidth, buttonHeight));
  inputButton.setFillColor(sf::Color(204, 199, 186));
  inputButton.setPosition((windowSize.x - buttonWidth) / 2, getButton_Position(buttonY));

  sf::Text inputText("NHAP HANG", font, 20);
  inputText.setFillColor(sf::Color(14, 64, 71));
  inputText.setPosition(inputButton.getPosition().x + 25, inputButton.getPosition().y + 5);

  sf::RectangleShape exitButton(sf::Vector2f(buttonWidth, buttonHeight));
  exitButton.setFillColor(sf::Color(204, 199, 186));
  exitButton.setPosition((windowSize.x - buttonWidth) / 2, getButton_Position(buttonY));

  sf::Text exitText("EXIT", font, 20);
  exitText.setFillColor(sf::Color(14, 64, 71));
  exitText.setPosition(exitButton.getPosition().x + 75, exitButton.getPosition().y + 5);
  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
      if (event.type == sf::Event::Closed)
        window.close();

    if (event.type == sf::Event::MouseButtonPressed)
    {
      mPos = sf::Mouse::getPosition(window);
      if (outputButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mPos)))
      {
        isVisible = false;
        output();
      }
      else if (inputButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mPos)))
      {
        isVisible = false;
        input();
      }
      else if (exitButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mPos)))
      {
        window.close();
      }
    }

    window.draw(dialogBox);
    window.draw(dialogText);
    window.draw(inputButton);
    window.draw(inputText);
    window.draw(outputButton);
    window.draw(outputText);
    window.draw(exitButton);
    window.draw(exitText);
    window.display();
  }
}

void output()
{
  if (!font.loadFromFile("arial.ttf"))
  {
    return;
  }
  sf::RectangleShape dialogBox(sf::Vector2f(windowSize.x * 0.5f, windowSize.y * 0.07f));
  dialogBox.setFillColor(sf::Color(200, 200, 200));
  dialogBox.setOutlineThickness(2);
  dialogBox.setOutlineColor(sf::Color::Black);
  dialogBox.setPosition(windowSize.x * 0.25f, windowSize.y * 0.03f);

  sf::Text dialogText("OUTPUT", font, 20);
  dialogText.setFillColor(sf::Color::Blue);
  dialogText.setPosition(dialogBox.getPosition().x + 10, dialogBox.getPosition().y + 5);

  // Nút và text của nút
  float buttonY = windowSize.y * 0.3f;
  float buttonWidth = windowSize.x * 0.3f;
  float buttonHeight = windowSize.y * 0.07f;

  sf::RectangleShape outputButton(sf::Vector2f(buttonWidth, buttonHeight));
  outputButton.setFillColor(sf::Color(204, 199, 186));
  outputButton.setPosition((windowSize.x - buttonWidth) / 2, buttonY);

  sf::Text outputText("CAP NHAT XE DA DEN", font, 20);
  outputText.setFillColor(sf::Color(14, 64, 71));
  outputText.setPosition(outputButton.getPosition().x + 25, outputButton.getPosition().y + 5);

  sf::RectangleShape inputButton(sf::Vector2f(buttonWidth, buttonHeight));
  inputButton.setFillColor(sf::Color(204, 199, 186));
  inputButton.setPosition((windowSize.x - buttonWidth) / 2, getButton_Position(buttonY));

  sf::Text inputText("XUAT HANG", font, 20);
  inputText.setFillColor(sf::Color(14, 64, 71));
  inputText.setPosition(inputButton.getPosition().x + 25, inputButton.getPosition().y + 5);

  sf::RectangleShape exitButton(sf::Vector2f(buttonWidth, buttonHeight));
  exitButton.setFillColor(sf::Color(204, 199, 186));
  exitButton.setPosition((windowSize.x - buttonWidth) / 2, getButton_Position(buttonY));

  sf::Text exitText("EXIT", font, 20);
  exitText.setFillColor(sf::Color(14, 64, 71));
  exitText.setPosition(exitButton.getPosition().x + 75, exitButton.getPosition().y + 5);
}

void search()
{
  if (!font.loadFromFile("arial.ttf"))
  {
    return;
  }
  sf::RectangleShape dialogBox(sf::Vector2f(windowSize.x * 0.5f, windowSize.y * 0.07f));
  dialogBox.setFillColor(sf::Color(200, 200, 200));
  dialogBox.setOutlineThickness(2);
  dialogBox.setOutlineColor(sf::Color::Black);
  dialogBox.setPosition(windowSize.x * 0.25f, windowSize.y * 0.03f);

  sf::Text dialogText("SEARCH", font, 20);
  dialogText.setFillColor(sf::Color::Blue);
  dialogText.setPosition(dialogBox.getPosition().x + 10, dialogBox.getPosition().y + 5);

  // Nút và text của nút
  float buttonY = windowSize.y * 0.3f;
  float buttonWidth = windowSize.x * 0.3f;
  float buttonHeight = windowSize.y * 0.07f;

  sf::RectangleShape exitButton(sf::Vector2f(buttonWidth, buttonHeight));
  exitButton.setFillColor(sf::Color(204, 199, 186));
  exitButton.setPosition((windowSize.x - buttonWidth) / 2, getButton_Position(buttonY));

  sf::Text exitText("EXIT", font, 20);
  exitText.setFillColor(sf::Color(14, 64, 71));
  exitText.setPosition(exitButton.getPosition().x + 75, exitButton.getPosition().y + 5);
}

void search(Kho *khoArr[], int num)
{
    sf::Text promptText("Nhap ma don hang:", font, 20);
    promptText.setFillColor(sf::Color::Black);
    promptText.setPosition(200, 30);

    std::string ma;
    sf::Text inputText("", font, 20);
    inputText.setFillColor(sf::Color::Black);
    inputText.setPosition(210, 80);

    sf::Text resultText("", font, 20);
    resultText.setFillColor(sf::Color::Red);
    resultText.setPosition(220, 250);

    // Hộp thoại nhập mã đơn hàng
    sf::RectangleShape inputBox(sf::Vector2f(400, 50));
    inputBox.setFillColor(sf::Color::White);
    inputBox.setOutlineThickness(2);
    inputBox.setOutlineColor(sf::Color::Black);
    inputBox.setPosition(200, 70);

    // Hộp thoại thông báo
    sf::RectangleShape messageBox(sf::Vector2f(400, 150));
    messageBox.setFillColor(sf::Color(220, 220, 220));
    messageBox.setOutlineThickness(2);
    messageBox.setOutlineColor(sf::Color::Black);
    messageBox.setPosition(200, 250);

    // Nút "OK"
    sf::RectangleShape okButton(sf::Vector2f(85, 40));
    okButton.setFillColor(sf::Color(204, 199, 186));
    okButton.setPosition(250, 350);

    sf::Text okText("Nhap lai", font, 20);
    okText.setFillColor(sf::Color::Blue);
    okText.setPosition(270, 355);

    // Nút "Exit"
    sf::RectangleShape exitButton(sf::Vector2f(130, 40));
    exitButton.setFillColor(sf::Color(204, 199, 186));
    exitButton.setPosition(350, 350);

    sf::Text exitText("Quay lai menu", font, 20);
    exitText.setFillColor(sf::Color::Blue);
    exitText.setPosition(400, 355);

    bool searching = true;
    bool showMessage = false; // Biến để kiểm soát việc hiển thị hộp thoại thông báo

    while (searching && window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            // Nhận mã đơn hàng từ bàn phím
            if (event.type == sf::Event::TextEntered && !showMessage)
            {
                if (event.text.unicode == '\b' && !ma.empty())
                {
                    ma.pop_back(); // Xóa ký tự cuối
                }
                else if (event.text.unicode < 128 && event.text.unicode != '\b')
                {
                    ma += static_cast<char>(event.text.unicode);
                }
                inputText.setString(ma);
            }

            // Kiểm tra khi nhấn Enter
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter && !showMessage)
            {
                bool found = false;
                for (int i = 0; i < num; i++)
                {
                    DonHang *DH = khoArr[i]->searchDH(ma);
                    if (DH)
                    {
                        resultText.setPosition(220, 250);
                        okText.setPosition(270, 400);
                        okButton.setPosition(250, 395);
                        exitText.setPosition(400, 400);
                        exitButton.setPosition(350, 395);
                        messageBox.setSize(sf::Vector2f(400, 200));
                        resultText.setString("Don hang da tim thay:");
                        DH->showInfo(resultText); // Hiển thị thông tin đơn hàng
                        found = true;
                        break;
                    }
                }
                if (!found)
                {
                    okButton.setPosition(250, 350);
                    exitText.setPosition(400, 355);
                    exitButton.setPosition(350, 350);
                    resultText.setString("Khong tim thay thong tin don hang.");
                    messageBox.setSize(sf::Vector2f(400, 150));
                    resultText.setPosition(220, 280);
                    okText.setPosition(270, 355);
                }
                showMessage = true; // Hiện hộp thoại thông báo
            }

            // Xử lý nút "OK"
            if (showMessage && event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (okButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                {
                    showMessage = false;     // Ẩn hộp thoại thông báo
                    ma.clear();              // Xóa nội dung đã nhập
                    inputText.setString(""); // Đặt lại văn bản nhập
                }
                // Xử lý nút "Exit"
                else if (exitButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                {
                    return; // Đóng cửa sổ
                }
            }
        }

        // Vẽ giao diện
        window.clear();
        window.draw(showbackground);
        window.draw(promptText);
        window.draw(inputBox);
        window.draw(inputText);

        if (showMessage)
        {
            window.draw(messageBox);
            window.draw(resultText);
            window.draw(okButton);
            window.draw(okText);
            window.draw(exitButton);
            window.draw(exitText);
        }

        window.display();
    }
}

void nhap_bks(Truck *truckArr[], int num, User user, int key)
{
    RectangleShape inputBox(Vector2f(400, 50));
    inputBox.setFillColor(Color::White);
    inputBox.setOutlineThickness(2);
    inputBox.setOutlineColor(Color::Black);
    inputBox.setPosition(200, 200);

    Text promptText("Nhap BKS:", font, 20);
    promptText.setFillColor(Color::Black);
    promptText.setPosition(200, 150);

    Text enteredText("", font, 20);
    enteredText.setFillColor(Color::Black);
    enteredText.setPosition(210, 210);

    RectangleShape messageBox(Vector2f(400, 150));
    messageBox.setFillColor(Color(220, 220, 220));
    messageBox.setOutlineThickness(2);
    messageBox.setOutlineColor(Color::Black);
    messageBox.setPosition(200, 250);

    Text resultText("", font, 20);
    resultText.setFillColor(Color::Red);
    resultText.setPosition(220, 270);

    RectangleShape okButton(Vector2f(80, 40));
    okButton.setFillColor(Color(204, 199, 186));
    okButton.setPosition(280, 350);

    Text okText("Continue", font, 20);
    okText.setFillColor(Color::Blue);
    okText.setPosition(300, 355);

    RectangleShape exitButton(Vector2f(80, 40));
    exitButton.setFillColor(Color(204, 199, 186));
    exitButton.setPosition(380, 350);

    Text exitText("Exit", font, 20);
    exitText.setFillColor(Color::Blue);
    exitText.setPosition(400, 355);

    std::string bs;
    bool check = false;
    bool showMessage = false;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (showMessage)
            {
                // Xử lý khi hiển thị thông báo
                if (event.type == Event::MouseButtonPressed)
                {
                    Vector2i mousePos = Mouse::getPosition(window);
                    if (okButton.getGlobalBounds().contains(static_cast<Vector2f>(mousePos)))
                    {
                        return; // Trở về menu chính
                    }
                }
            }
            else
            {
                // Xử lý nhập liệu khi chưa hiển thị thông báo
                if (event.type == Event::TextEntered)
                {
                    if (event.text.unicode == '\b' && !bs.empty())
                    {
                        bs.pop_back();
                    }
                    else if (event.text.unicode < 128 && event.text.unicode != '\b')
                    {
                        bs += static_cast<char>(event.text.unicode);
                    }
                    enteredText.setString(bs);
                }
                if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter)
                {
                    check = false;
                    for (int i = 0; i < num; i++)
                    {
                        if (truckArr[i]->getBKS() == bs)
                        {
                            if (key)
                                truckArr[i]->setStatus(1);
                            std::string tmp = truckArr[i]->getKhoHT();
                            truckArr[i]->setKhoHT(user.getKhoLamViec());
                            truckArr[i]->setKhoDen(tmp);
                            resultText.setString("Cap nhat thanh cong xe " + bs);
                            check = true;
                            showMessage = true; // Hiển thị thông báo
                            break;
                        }
                    }
                    if (!check)
                    {
                        resultText.setString("Khong ton tai xe " + bs);
                        showMessage = true; // Hiển thị thông báo nếu không tìm thấy xe
                    }
                }
            }
        }

        window.clear();
        window.draw(showbackground);
        window.draw(promptText);
        window.draw(inputBox);
        window.draw(enteredText);

        if (showMessage)
        {
            // Hiển thị hộp thông báo và nút "OK"
            window.clear();
            window.draw(showbackground);
            window.draw(messageBox);
            window.draw(resultText);
            window.draw(okButton);
            window.draw(okText);
        }

        window.display();
    }
}

void nhapDonHang(Truck *truckArr[], int num, User user, Kho *khoArr[], int n)
{
    // Khởi tạo các thành phần giao diện
    RectangleShape inputBox(Vector2f(400, 50));
    inputBox.setFillColor(Color::White);
    inputBox.setOutlineThickness(2);
    inputBox.setOutlineColor(Color::Black);
    inputBox.setPosition(200, 100);

    Text promptText("Nhap BKS:", font, 20);
    promptText.setFillColor(Color::Black);
    promptText.setPosition(200, 50);

    Text enteredText("", font, 20);
    enteredText.setFillColor(Color::Black);
    enteredText.setPosition(210, 110);

    // Thông báo
    RectangleShape messageBox(Vector2f(400, 150));
    messageBox.setFillColor(Color(220, 220, 220));
    messageBox.setOutlineThickness(2);
    messageBox.setOutlineColor(Color::Black);
    messageBox.setPosition(200, 250);

    Text resultText("", font, 20);
    resultText.setFillColor(Color::Red);
    resultText.setPosition(220, 270);

    // Nút "OK"
    RectangleShape okButton(Vector2f(80, 40));
    okButton.setFillColor(Color(204, 199, 186));
    okButton.setPosition(360, 350);

    Text okText("OK", font, 20);
    okText.setFillColor(Color::Blue);
    okText.setPosition(380, 355);

    // Nút nhập đơn hàng
    RectangleShape orderInputBox(Vector2f(400, 50));
    orderInputBox.setFillColor(Color::White);
    orderInputBox.setOutlineThickness(2);
    orderInputBox.setOutlineColor(Color::Black);
    orderInputBox.setPosition(200, 400);

    Text orderPromptText("Nhap ma don hang (nhap 00 de thoat):", font, 20);
    orderPromptText.setFillColor(Color::Black);
    orderPromptText.setPosition(200, 360);

    Text orderEnteredText("", font, 20);
    orderEnteredText.setFillColor(Color::Black);
    orderEnteredText.setPosition(210, 410);

    string bs, ma;
    bool check = false;
    bool showMessage = false;
    bool orderInputVisible = false;
    Truck *truck = NULL;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            string bs;
            cout << "Nhap BKS: ";
            cin >> bs;

            Truck *truck = NULL;
            for (int i = 0; i < num; i++)
            {
                if (truckArr[i]->getBKS() == bs)
                {
                    truck = truckArr[i];
                    break;
                }
            }

            if (truck == NULL)
            {
                while (!Keyboard::isKeyPressed(Keyboard::Enter) || Event::MouseButtonPressed)
                    cout << "Khong ton tai xe " << bs << endl;
                return;
            }
            if (truck->getStatus() == 0)
            {
                cout << "Xe van chua den noi khong the nhap hang" << endl;
                return;
            }

            // Xử lý nhập biển số
            if (event.type == Event::TextEntered)
            {
                if (event.text.unicode == '\b' && !bs.empty())
                {
                    bs.pop_back();
                }
                else if (event.text.unicode < 128 && event.text.unicode != '\b')
                {
                    bs += static_cast<char>(event.text.unicode);
                }
                enteredText.setString(bs);
            }

            // Kiểm tra biển số khi nhấn Enter
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter)
            {
                check = false;
                for (int i = 0; i < num; i++)
                {
                    if (truckArr[i]->getBKS() == bs)
                    {
                        truck = truckArr[i];
                        check = true;
                        if (truck->getStatus() == 0)
                        {
                            resultText.setString("Xe van chua den noi, khong the nhap hang.");
                            showMessage = true;
                        }
                        else
                        {
                            resultText.setString("Xe " + bs + " da den. Nhap don hang:");
                            orderInputVisible = true; // Hiện hộp nhập đơn hàng
                        }

                        break;
                    }
                }
                if (!check)
                {
                    resultText.setString("Khong ton tai xe " + bs);
                    showMessage = true;
                }
            }

            // Xử lý sự kiện cho nút OK
            if (showMessage && event.type == Event::MouseButtonPressed)
            {
                Vector2i mousePos = Mouse::getPosition(window);
                if (okButton.getGlobalBounds().contains(static_cast<Vector2f>(mousePos)))
                {
                    if (!orderInputVisible)
                    {
                        return; // Trở về menu chính
                    }
                    showMessage = false; // Ẩn thông báo
                }
            }

            // Xử lý nhập mã đơn hàng
            if (orderInputVisible)
            {
                if (event.type == Event::TextEntered)
                {
                    if (event.text.unicode == '\b' && !ma.empty())
                    {
                        ma.pop_back();
                    }
                    else if (event.text.unicode < 128 && event.text.unicode != '\b')
                    {
                        ma += static_cast<char>(event.text.unicode);
                    }
                    orderEnteredText.setString(ma);
                }

                // Kiểm tra mã đơn hàng khi nhấn Enter
                if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter)
                {
                    if (ma == "00")
                    {
                        orderInputVisible = false; // Quay lại màn nhập biển số
                        ma.clear();
                        orderEnteredText.setString(""); // Xóa nội dung đã nhập
                        resultText.setString("");       // Xóa thông báo
                        showMessage = true;             // Hiện nút "OK"
                        continue;
                    }

                    DonHang *ord = truck->DH.find(ma);
                    if (ord == NULL)
                    {
                        resultText.setString("Khong tim thay don hang " + ma + " tren xe.");
                        showMessage = true;
                        continue;
                    }

                    // Xử lý nhập hàng
                    std::string khoName = user.getKhoLamViec();
                    Kho *kho = NULL;
                    for (int i = 0; i < n; i++)
                    {
                        if (khoArr[i]->getName() == khoName)
                        {
                            kho = khoArr[i];
                            break;
                        }
                    }
                    if (kho)
                    {
                        truck->xuongTai(*ord, *kho);
                        resultText.setString("Nhap hang thanh cong cho don hang " + ma);
                        showMessage = true;
                    }
                }
            }
            else
            {
            }
        }

        // Vẽ giao diện
        window.clear();
        window.draw(showbackground);
        window.draw(promptText);
        window.draw(inputBox);
        window.draw(enteredText);

        // Nếu có thông báo, vẽ nó
        if (showMessage)
        {
            window.clear();
            window.draw(showbackground);
            window.draw(messageBox);
            window.draw(resultText);
            window.draw(okButton);
            window.draw(okText);
        }

        // Nếu đang nhập mã đơn hàng, vẽ nó
        if (orderInputVisible)
        {
            window.clear();
            window.draw(showbackground);
            window.draw(orderInputBox);
            window.draw(orderPromptText);
            window.draw(orderEnteredText);
        }

        window.display();
    }
}

void xuatDonHang(Truck *truckArr[], int num, User user, Kho *khoArr[], int n)
{
    // Khởi tạo các thành phần giao diện
    RectangleShape inputBox(Vector2f(400, 50));
    inputBox.setFillColor(Color::White);
    inputBox.setOutlineThickness(2);
    inputBox.setOutlineColor(Color::Black);
    inputBox.setPosition(200, 100);

    Text promptText("Nhap BKS:", font, 20);
    promptText.setFillColor(Color::Black);
    promptText.setPosition(200, 50);

    Text enteredText("", font, 20);
    enteredText.setFillColor(Color::Black);
    enteredText.setPosition(210, 110);

    // Thông báo
    RectangleShape messageBox(Vector2f(400, 150));
    messageBox.setFillColor(Color(220, 220, 220));
    messageBox.setOutlineThickness(2);
    messageBox.setOutlineColor(Color::Black);
    messageBox.setPosition(200, 250);

    Text resultText("", font, 20);
    resultText.setFillColor(Color::Red);
    resultText.setPosition(220, 270);

    // Nút "OK"
    RectangleShape okButton(Vector2f(80, 40));
    okButton.setFillColor(Color(204, 199, 186));
    okButton.setPosition(360, 350);

    Text okText("OK", font, 20);
    okText.setFillColor(Color::Blue);
    okText.setPosition(380, 355);

    // Biến lưu trạng thái
    std::string bs;
    bool showMessage = false;
    bool truckFound = false;
    Truck *selectedTruck = NULL;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }

            // Xử lý sự kiện cho nút OK
            if (showMessage && event.type == Event::MouseButtonPressed)
            {
                Vector2i mousePos = Mouse::getPosition(window);
                if (okButton.getGlobalBounds().contains(static_cast<Vector2f>(mousePos)))
                {
                    showMessage = false; // Ẩn thông báo
                    if (selectedTruck)
                    {
                        // Thực hiện xuất hàng khi xe đã được chọn
                        while (true)
                        {
                            std::string khoDen = selectedTruck->getKhoDen();
                            Kho *kho = NULL;

                            // Hiển thị danh sách đơn hàng trong kho
                            for (int j = 0; j < n; j++)
                            {
                                if (khoArr[j]->getName() == khoDen)
                                {
                                    kho = khoArr[j];
                                    kho->showBlock(khoDen);
                                    break;
                                }
                            }

                            std::string ma;
                            // Nhập mã đơn hàng
                            Text orderPromptText("Nhap ma don hang (nhap 00 de thoat):", font, 20);
                            orderPromptText.setFillColor(Color::Black);
                            orderPromptText.setPosition(200, 400);
                            window.draw(orderPromptText);
                            window.display();

                            // Nhập mã đơn hàng từ người dùng
                            while (true)
                            {
                                // Lấy mã đơn hàng
                                // Tương tự như nhập mã biển số, thêm logic xử lý để nhập
                                // Nếu nhập "00", thoát khỏi vòng lặp

                                // Giả sử bạn đã có mã đơn hàng trong biến 'ma'
                                if (ma == "00")
                                    break;

                                if (kho)
                                {
                                    Block *block = (Block *)kho->blocks.find(khoDen);
                                    if (block)
                                    {
                                        DonHang *ord = block->find(ma);
                                        if (ord)
                                        {
                                            selectedTruck->lenTai(*ord, *block);
                                            resultText.setString("Xuat hang thanh cong cho don hang " + ma + ".");
                                        }
                                        else
                                        {
                                            resultText.setString("Khong tim thay don hang " + ma + " trong block.");
                                        }
                                    }
                                }
                            }

                            int b;
                            // Chốt hoàn thành điểm
                            resultText.setString("Nhan 1 de chot hoan thanh diem va cho xe di: ");
                            window.draw(resultText);
                            window.display();
                            // Nhận input cho 'b' từ người dùng
                            if (b == 1)
                            {
                                selectedTruck->setStatus(0);
                            }
                        }
                    }
                    return; // Trở về menu chính nếu không còn xe nào
                }
            }

            // Xử lý nhập biển số
            if (event.type == Event::TextEntered)
            {
                if (event.text.unicode == '\b' && !bs.empty())
                {
                    bs.pop_back();
                }
                else if (event.text.unicode < 128 && event.text.unicode != '\b')
                {
                    bs += static_cast<char>(event.text.unicode);
                }
                enteredText.setString(bs);
            }

            // Kiểm tra biển số khi nhấn Enter
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter)
            {
                truckFound = false;
                for (int i = 0; i < num; i++)
                {
                    if (truckArr[i]->getBKS() == bs)
                    {
                        selectedTruck = truckArr[i];
                        if (selectedTruck->getStatus() == 0)
                        {
                            resultText.setString("Xe van chua den noi, khong the xuat hang.");
                        }
                        else
                        {
                            resultText.setString("Xe " + bs + " da den. Xuất hàng:");
                        }
                        showMessage = true;
                        truckFound = true;
                        break;
                    }
                }
                if (!truckFound)
                {
                    resultText.setString("Khong ton tai xe " + bs + ".");
                    showMessage = true;
                }
            }
        }

        // Vẽ giao diện
        window.clear();
        window.draw(showbackground);
        window.draw(promptText);
        window.draw(inputBox);
        window.draw(enteredText);

        // Nếu có thông báo, vẽ nó
        if (showMessage)
        {
            window.draw(messageBox);
            window.draw(resultText);
            window.draw(okButton);
            window.draw(okText);
        }

        window.display();
    }
}

// bks_nhapHang += nhapHang
bool bks_nhapHang(Truck *truckArr[], int num, User user, Kho *khoArr[], int n, string bs)
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

    Truck *truck = NULL;
    for (int i = 0; i < num; i++)
        if (truckArr[i]->getBKS() == bs)
        {
            truck = truckArr[i];
            break;
        }

    if (truck == NULL)
    {
        resultText.setString("Khong ton tai xe " + bs);
        resultText.setPosition(300, 280);
    }
    else if (truck->getStatus() == 0)
    {
        resultText.setString("Xe " + bs + " van chua den!");
        resultText.setPosition(300, 280);
    }
    else
    {
        nhapHang(truck, user, khoArr, n);
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


void nhapHang(Truck *truck, User user, Kho *khoArr[], int n)
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

            if (s_nhap(ma))
            {
                if (nhapHang_check(khoArr, truck, user, ma, n))
                    continue;
                continueInput = false;
            }
            else
                continueInput = false;
        }
    }
}

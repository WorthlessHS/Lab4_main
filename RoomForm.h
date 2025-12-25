#pragma once

#include <msclr/marshal_cppstd.h>
#include "Hotel.h"
#include "Room.h"

namespace HotelSystem {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class RoomForm : public Form
    {
    private:
        Hotel* hotel;
        Room* editingRoom;
        bool isEditMode;

        Label^ labelRoomNumber;
        TextBox^ textRoomNumber;
        Label^ labelRoomType;
        ComboBox^ comboRoomType;
        Label^ labelBasePrice;
        TextBox^ textBasePrice;
        Label^ labelDiscountType;
        ComboBox^ comboDiscountType;
        Label^ labelDiscountPercent;
        TextBox^ textDiscountPercent;
        Button^ buttonOK;
        Button^ buttonCancel;

        void InitializeComponent()
        {
            this->labelRoomNumber = gcnew Label();
            this->textRoomNumber = gcnew TextBox();
            this->labelRoomType = gcnew Label();
            this->comboRoomType = gcnew ComboBox();
            this->labelBasePrice = gcnew Label();
            this->textBasePrice = gcnew TextBox();
            this->labelDiscountType = gcnew Label();
            this->comboDiscountType = gcnew ComboBox();
            this->labelDiscountPercent = gcnew Label();
            this->textDiscountPercent = gcnew TextBox();
            this->buttonOK = gcnew Button();
            this->buttonCancel = gcnew Button();

            this->SuspendLayout();

            // labelRoomNumber
            this->labelRoomNumber->AutoSize = true;
            this->labelRoomNumber->Location = System::Drawing::Point(15, 15);
            this->labelRoomNumber->Text = L"Номер комнаты:";

            // textRoomNumber
            this->textRoomNumber->Location = System::Drawing::Point(150, 12);
            this->textRoomNumber->Size = System::Drawing::Size(150, 20);

            // labelRoomType
            this->labelRoomType->AutoSize = true;
            this->labelRoomType->Location = System::Drawing::Point(15, 45);
            this->labelRoomType->Text = L"Тип номера:";

            // comboRoomType
            this->comboRoomType->Location = System::Drawing::Point(150, 42);
            this->comboRoomType->Size = System::Drawing::Size(150, 21);
            this->comboRoomType->Items->Add(L"Стандартный");
            this->comboRoomType->Items->Add(L"Люкс");
            this->comboRoomType->DropDownStyle = ComboBoxStyle::DropDownList;
            this->comboRoomType->SelectedIndex = 0;

            // labelBasePrice
            this->labelBasePrice->AutoSize = true;
            this->labelBasePrice->Location = System::Drawing::Point(15, 75);
            this->labelBasePrice->Text = L"Базовая стоимость:";

            // textBasePrice
            this->textBasePrice->Location = System::Drawing::Point(150, 72);
            this->textBasePrice->Size = System::Drawing::Size(150, 20);

            // labelDiscountType
            this->labelDiscountType->AutoSize = true;
            this->labelDiscountType->Location = System::Drawing::Point(15, 105);
            this->labelDiscountType->Text = L"Тип скидки:";

            // comboDiscountType
            this->comboDiscountType->Location = System::Drawing::Point(150, 102);
            this->comboDiscountType->Size = System::Drawing::Size(150, 21);
            this->comboDiscountType->Items->Add(L"Без скидки");
            this->comboDiscountType->Items->Add(L"Процентная");
            this->comboDiscountType->DropDownStyle = ComboBoxStyle::DropDownList;
            this->comboDiscountType->SelectedIndex = 0;
            this->comboDiscountType->SelectedIndexChanged += gcnew EventHandler(this, &RoomForm::comboDiscountType_SelectedIndexChanged);

            // labelDiscountPercent
            this->labelDiscountPercent->AutoSize = true;
            this->labelDiscountPercent->Location = System::Drawing::Point(15, 135);
            this->labelDiscountPercent->Text = L"Процент скидки (%):";

            // textDiscountPercent
            this->textDiscountPercent->Location = System::Drawing::Point(150, 132);
            this->textDiscountPercent->Size = System::Drawing::Size(150, 20);
            this->textDiscountPercent->Enabled = false;

            // buttonOK
            this->buttonOK->Location = System::Drawing::Point(150, 170);
            this->buttonOK->Size = System::Drawing::Size(70, 30);
            this->buttonOK->Text = L"ОК";
            this->buttonOK->Click += gcnew EventHandler(this, &RoomForm::buttonOK_Click);

            // buttonCancel
            this->buttonCancel->Location = System::Drawing::Point(230, 170);
            this->buttonCancel->Size = System::Drawing::Size(70, 30);
            this->buttonCancel->Text = L"Отмена";
            this->buttonCancel->Click += gcnew EventHandler(this, &RoomForm::buttonCancel_Click);

            // RoomForm
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(320, 220);
            this->Controls->Add(this->labelRoomNumber);
            this->Controls->Add(this->textRoomNumber);
            this->Controls->Add(this->labelRoomType);
            this->Controls->Add(this->comboRoomType);
            this->Controls->Add(this->labelBasePrice);
            this->Controls->Add(this->textBasePrice);
            this->Controls->Add(this->labelDiscountType);
            this->Controls->Add(this->comboDiscountType);
            this->Controls->Add(this->labelDiscountPercent);
            this->Controls->Add(this->textDiscountPercent);
            this->Controls->Add(this->buttonOK);
            this->Controls->Add(this->buttonCancel);
            this->MaximizeBox = false;
            this->MinimizeBox = false;
            this->StartPosition = FormStartPosition::CenterParent;
            this->Text = L"Добавление номера";
            this->ResumeLayout(false);
            this->PerformLayout();
        }

    public:
        // Конструктор для режима добавления
        RoomForm(Hotel* h) : hotel(h), editingRoom(nullptr), isEditMode(false)
        {
            InitializeComponent();
            this->Text = L"Добавление номера";
        }

        // Конструктор для режима редактирования
        RoomForm(Hotel* h, Room* room) : hotel(h), editingRoom(room), isEditMode(true)
        {
            InitializeComponent();
            this->Text = L"Редактирование номера";
            this->textRoomNumber->ReadOnly = true;

            // Заполняем поля существующими данными
            this->textRoomNumber->Text = room->getRoomNumber().ToString();
            this->textBasePrice->Text = room->getBasePrice().ToString("F2");

            // Тип номера
            StandardRoom* stdRoom = dynamic_cast<StandardRoom*>(room);
            if (stdRoom) {
                this->comboRoomType->SelectedIndex = 0;
            } else {
                this->comboRoomType->SelectedIndex = 1;
            }

            // Тип скидки
            if (room->hasNoDiscount()) {
                this->comboDiscountType->SelectedIndex = 0;
                this->textDiscountPercent->Enabled = false;
            } else {
                this->comboDiscountType->SelectedIndex = 1;
                this->textDiscountPercent->Enabled = true;
                this->textDiscountPercent->Text = room->getDiscountPercentage().ToString("F2");
            }
        }

    private:
        System::Void comboDiscountType_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
        {
            if (this->comboDiscountType->SelectedIndex == 0) {
                this->textDiscountPercent->Enabled = false;
                this->textDiscountPercent->Clear();
            } else {
                this->textDiscountPercent->Enabled = true;
            }
        }

        System::Void buttonOK_Click(System::Object^ sender, System::EventArgs^ e)
        {
            // Проверка полей
            String^ errorMsg = ValidateFields();
            if (!String::IsNullOrEmpty(errorMsg)) {
                MessageBox::Show(errorMsg, L"Ошибка ввода", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            // Парсим значения
            int roomNumber = System::Int32::Parse(this->textRoomNumber->Text);
            double basePrice = System::Double::Parse(this->textBasePrice->Text);
            int roomType = this->comboRoomType->SelectedIndex; // 0 = Standard, 1 = Luxury
            int discountType = this->comboDiscountType->SelectedIndex; // 0 = NoDiscount, 1 = Percentage

            // Проверка уникальности номера (для режима добавления)
            if (!isEditMode && hotel->isRoomNumberExists(roomNumber)) {
                MessageBox::Show(L"Номер комнаты уже существует!", L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            // Проверка диапазона цены
            double minPrice = (roomType == 0) ? 100.0 : 5000.0;
            double maxPrice = (roomType == 0) ? 5000.0 : 15000.0;

            if (basePrice < minPrice || basePrice > maxPrice) {
                MessageBox::Show(String::Format(L"Базовая стоимость должна быть от {0} до {1}", 
                    (int)minPrice, (int)maxPrice), L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            // Создание или обновление Room
            if (isEditMode) {
                // В режиме редактирования просто обновляем существующий объект
                // (для упрощения - удаляем и создаем заново)
                int hotelIndex = -1;
                const std::vector<Room*>& rooms = hotel->getRooms();
                for (int i = 0; i < (int)rooms.size(); i++) {
                    if (rooms[i] == editingRoom) {
                        hotelIndex = i;
                        break;
                    }
                }

                if (hotelIndex != -1) {
                    hotel->removeRoomAt(hotelIndex);
                }
            }

            // Создаем новый Room с нужной стратегией скидок
            std::unique_ptr<PricingStrategy> strategy;
            if (discountType == 0) {
                strategy = std::make_unique<NoDiscount>();
            } else {
                double discountPercent = System::Double::Parse(this->textDiscountPercent->Text);
                strategy = std::make_unique<PercentageDiscount>(discountPercent);
            }

            Room* newRoom = nullptr;
            if (roomType == 0) {
                newRoom = new StandardRoom(roomNumber, basePrice, std::move(strategy));
            } else {
                newRoom = new LuxuryRoom(roomNumber, basePrice, std::move(strategy));
            }

            hotel->addRoom(newRoom);
            this->DialogResult = System::Windows::Forms::DialogResult::OK;
            this->Close();
        }

        System::Void buttonCancel_Click(System::Object^ sender, System::EventArgs^ e)
        {
            this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
            this->Close();
        }

        String^ ValidateFields()
        {
            // Номер комнаты
            if (String::IsNullOrWhiteSpace(this->textRoomNumber->Text)) {
                return L"Заполните номер комнаты!";
            }
            int roomNum;
            if (!System::Int32::TryParse(this->textRoomNumber->Text, roomNum)) {
                return L"Номер комнаты должен быть целым числом!";
            }
            if (roomNum < 1 || roomNum > 9999) {
                return L"Номер комнаты должен быть от 1 до 9999!";
            }

            // Базовая стоимость
            if (String::IsNullOrWhiteSpace(this->textBasePrice->Text)) {
                return L"Заполните базовую стоимость!";
            }
            double basePrice;
            if (!System::Double::TryParse(this->textBasePrice->Text, basePrice)) {
                return L"Базовая стоимость должна быть числом!";
            }
            if (basePrice <= 0) {
                return L"Базовая стоимость должна быть больше нуля!";
            }

            // Если выбрана процентная скидка
            if (this->comboDiscountType->SelectedIndex == 1) {
                if (String::IsNullOrWhiteSpace(this->textDiscountPercent->Text)) {
                    return L"Заполните процент скидки!";
                }
                double discountPercent;
                if (!System::Double::TryParse(this->textDiscountPercent->Text, discountPercent)) {
                    return L"Процент скидки должен быть числом!";
                }

                int roomType = this->comboRoomType->SelectedIndex;
                double maxDiscount = (roomType == 0) ? 100.0 : 50.0;

                if (discountPercent < 1 || discountPercent > maxDiscount) {
                    return String::Format(L"Процент скидки должен быть от 1 до {0}%!", (int)maxDiscount);
                }
                // Проверка выбора типа номера
                if (this->comboRoomType->SelectedIndex < 0) {
                    return L"Выберите тип номера!";
                }

                // Проверка выбора типа скидки
                if (this->comboDiscountType->SelectedIndex < 0) {
                    return L"Выберите тип скидки!";
                }

            }

            return nullptr;
        }
    };
}

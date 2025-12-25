#pragma once

#include <msclr/marshal_cppstd.h>
#include "Hotel.h"
#include "Room.h"
#include "RoomForm.h"
#include <fstream>
#include <sstream>
#include <iomanip>

namespace HotelSystem {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class MainForm : public Form
    {
    private:
        Hotel* hotel;

        DataGridView^ dataGridView;
        Label^ labelAverage;
        Button^ buttonAdd;
        Button^ buttonEdit;
        Button^ buttonDelete;
        Button^ buttonLoad;
        Button^ buttonSave;
        Button^ buttonSortNumber;
        Button^ buttonSortBasePrice;
        Button^ buttonSortFinalPrice;

        bool sortNumberAscending = true;
        bool sortBasePriceAscending = true;
        bool sortFinalPriceAscending = true;

        void InitializeComponent()
        {
            this->dataGridView = gcnew DataGridView();
            this->labelAverage = gcnew Label();
            this->buttonAdd = gcnew Button();
            this->buttonEdit = gcnew Button();
            this->buttonDelete = gcnew Button();
            this->buttonLoad = gcnew Button();
            this->buttonSave = gcnew Button();
            this->buttonSortNumber = gcnew Button();
            this->buttonSortBasePrice = gcnew Button();
            this->buttonSortFinalPrice = gcnew Button();

            this->SuspendLayout();

            // dataGridView
            this->dataGridView->Location = System::Drawing::Point(10, 10);
            this->dataGridView->Size = System::Drawing::Size(760, 300);
            this->dataGridView->AllowUserToAddRows = false;
            this->dataGridView->AllowUserToDeleteRows = false;
            this->dataGridView->ReadOnly = true;
            this->dataGridView->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
            this->dataGridView->MultiSelect = false;
            this->dataGridView->ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode::AutoSize;

            this->dataGridView->Columns->Add(L"Номер", L"Номер");
            this->dataGridView->Columns->Add(L"Тип", L"Тип");
            this->dataGridView->Columns->Add(L"Базовая цена", L"Базовая цена");
            this->dataGridView->Columns->Add(L"Финальная цена", L"Финальная цена");
            this->dataGridView->Columns->Add(L"Скидка", L"Скидка");

            for each(DataGridViewColumn ^ col in this->dataGridView->Columns)
            {
                col->SortMode = DataGridViewColumnSortMode::NotSortable;
            }

            // labelAverage
            this->labelAverage->Location = System::Drawing::Point(10, 320);
            this->labelAverage->Size = System::Drawing::Size(760, 30);
            this->labelAverage->Text = L"Средняя стоимость: ---";
            this->labelAverage->Font =
                gcnew System::Drawing::Font(L"Arial", 11, System::Drawing::FontStyle::Bold);

            // buttonAdd
            this->buttonAdd->Location = System::Drawing::Point(10, 360);
            this->buttonAdd->Size = System::Drawing::Size(80, 30);
            this->buttonAdd->Text = L"Добавить";
            this->buttonAdd->Click += gcnew EventHandler(this, &MainForm::buttonAdd_Click);

            // buttonEdit
            this->buttonEdit->Location = System::Drawing::Point(100, 360);
            this->buttonEdit->Size = System::Drawing::Size(80, 30);
            this->buttonEdit->Text = L"Изменить";
            this->buttonEdit->Click += gcnew EventHandler(this, &MainForm::buttonEdit_Click);

            // buttonDelete
            this->buttonDelete->Location = System::Drawing::Point(190, 360);
            this->buttonDelete->Size = System::Drawing::Size(80, 30);
            this->buttonDelete->Text = L"Удалить";
            this->buttonDelete->Click += gcnew EventHandler(this, &MainForm::buttonDelete_Click);

            // buttonLoad
            this->buttonLoad->Location = System::Drawing::Point(280, 360);
            this->buttonLoad->Size = System::Drawing::Size(100, 30);
            this->buttonLoad->Text = L"Загрузить";
            this->buttonLoad->Click += gcnew EventHandler(this, &MainForm::buttonLoad_Click);

            // buttonSave
            this->buttonSave->Location = System::Drawing::Point(390, 360);
            this->buttonSave->Size = System::Drawing::Size(100, 30);
            this->buttonSave->Text = L"Сохранить";
            this->buttonSave->Click += gcnew EventHandler(this, &MainForm::buttonSave_Click);

            // === Сортировка ===

            // buttonSortNumber
            this->buttonSortNumber->Location = System::Drawing::Point(500, 360);
            this->buttonSortNumber->Size = System::Drawing::Size(85, 30);
            this->buttonSortNumber->Text = L"По ном.";
            this->buttonSortNumber->Click += gcnew EventHandler(this, &MainForm::buttonSortNumber_Click);

            // buttonSortBasePrice
            this->buttonSortBasePrice->Location = System::Drawing::Point(590, 360);
            this->buttonSortBasePrice->Size = System::Drawing::Size(85, 30);
            this->buttonSortBasePrice->Text = L"По баз.";
            this->buttonSortBasePrice->Click += gcnew EventHandler(this, &MainForm::buttonSortBasePrice_Click);

            // buttonSortFinalPrice
            this->buttonSortFinalPrice->Location = System::Drawing::Point(680, 360);
            this->buttonSortFinalPrice->Size = System::Drawing::Size(85, 30);
            this->buttonSortFinalPrice->Text = L"По итог.";
            this->buttonSortFinalPrice->Click += gcnew EventHandler(this, &MainForm::buttonSortFinalPrice_Click);

            System::Drawing::Font^ sortFont = gcnew System::Drawing::Font(L"Segoe UI Symbol", 9);

            this->buttonSortNumber->Font = sortFont;
            this->buttonSortBasePrice->Font = sortFont;
            this->buttonSortFinalPrice->Font = sortFont;

            this->buttonSortNumber->UseCompatibleTextRendering = true;
            this->buttonSortBasePrice->UseCompatibleTextRendering = true;
            this->buttonSortFinalPrice->UseCompatibleTextRendering = true;

            // MainForm
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(780, 410);
            this->Controls->Add(this->dataGridView);
            this->Controls->Add(this->labelAverage);
            this->Controls->Add(this->buttonAdd);
            this->Controls->Add(this->buttonEdit);
            this->Controls->Add(this->buttonDelete);
            this->Controls->Add(this->buttonLoad);
            this->Controls->Add(this->buttonSave);
            this->Controls->Add(this->buttonSortNumber);
            this->Controls->Add(this->buttonSortBasePrice);
            this->Controls->Add(this->buttonSortFinalPrice);
            this->StartPosition = FormStartPosition::CenterScreen;
            this->Text = L"Система управления гостиницей";

            this->ResumeLayout(false);
        }

    public:
        MainForm()
        {
            InitializeComponent();
            hotel = new Hotel();
            UpdateSortButtonText();
            RefreshGrid();
        }

        ~MainForm()
        {
            if (hotel) {
                delete hotel;
            }
        }

    private:
        void UpdateSortButtonText()
        {
            buttonSortNumber->Text = L"По ном." + (sortNumberAscending ? L" ▲" : L" ▼");
            buttonSortBasePrice->Text = L"По баз." + (sortBasePriceAscending ? L" ▲" : L" ▼");
            buttonSortFinalPrice->Text = L"По итог." + (sortFinalPriceAscending ? L" ▲" : L" ▼");
        }

        void RefreshGrid()
        {
            this->dataGridView->Rows->Clear();
            const std::vector<Room*>& rooms = hotel->getRooms();

            for (size_t i = 0; i < rooms.size(); i++) {
                Room* room = rooms[i];
                array<String^>^ row = gcnew array<String^>(5);
                row[0] = room->getRoomNumber().ToString();
                row[1] = gcnew String(room->getRoomType().c_str());
                row[2] = room->getBasePrice().ToString("F2");
                row[3] = room->calculatePrice().ToString("F2");

                String^ discountStr;
                if (room->hasNoDiscount()) {
                    discountStr = L"Без скидки";
                }
                else {
                    discountStr = room->getDiscountPercentage().ToString("F1") + L"%";
                }
                row[4] = discountStr;

                int rowIndex = this->dataGridView->Rows->Add(row);
                this->dataGridView->Rows[rowIndex]->Tag = System::IntPtr(room);
            }

            UpdateAverageLabel();
        }

        void UpdateAverageLabel()
        {
            try {
                double avg = hotel->calculateAveragePrice();
                this->labelAverage->Text =
                    "Средняя стоимость: " + avg.ToString("F2") + " руб.";
            }
            catch (const std::exception&) {
                this->labelAverage->Text =
                    gcnew String(L"Средняя стоимость: нет номеров");
            }
        }

        System::Void buttonAdd_Click(System::Object^ sender, System::EventArgs^ e)
        {
            RoomForm^ form = gcnew RoomForm(hotel);
            if (form->ShowDialog(this) == System::Windows::Forms::DialogResult::OK) {
                RefreshGrid();
            }
        }

        System::Void buttonEdit_Click(System::Object^ sender, System::EventArgs^ e)
        {
            if (this->dataGridView->SelectedRows->Count == 0) {
                MessageBox::Show(L"Выберите номер для редактирования!",
                    L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }

            DataGridViewRow^ selectedRow = this->dataGridView->SelectedRows[0];

            System::IntPtr ptr = safe_cast<System::IntPtr>(selectedRow->Tag);
            Room* room = static_cast<Room*>(ptr.ToPointer());

            RoomForm^ form = gcnew RoomForm(hotel, room);
            if (form->ShowDialog(this) == System::Windows::Forms::DialogResult::OK) {
                RefreshGrid();
            }
        }

        System::Void buttonDelete_Click(System::Object^ sender, System::EventArgs^ e)
        {
            if (this->dataGridView->SelectedRows->Count == 0) {
                MessageBox::Show(L"Выберите номер для удаления!",
                    L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }

            if (MessageBox::Show(L"Вы уверены?", L"Подтверждение удаления",
                MessageBoxButtons::YesNo, MessageBoxIcon::Question)
                != System::Windows::Forms::DialogResult::Yes) {
                return;
            }

            DataGridViewRow^ selectedRow = this->dataGridView->SelectedRows[0];

            System::IntPtr ptr = safe_cast<System::IntPtr>(selectedRow->Tag);
            Room* room = static_cast<Room*>(ptr.ToPointer());

            const std::vector<Room*>& rooms = hotel->getRooms();
            int index = -1;
            for (int i = 0; i < (int)rooms.size(); ++i) {
                if (rooms[i] == room) {
                    index = i;
                    break;
                }
            }

            if (index == -1) {
                MessageBox::Show(L"Ошибка: номер не найден во внутреннем списке.",
                    L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            hotel->removeRoomAt(index);
            RefreshGrid();
        }

        System::Void buttonLoad_Click(System::Object^ sender, System::EventArgs^ e)
        {
            OpenFileDialog^ dialog = gcnew OpenFileDialog();
            dialog->Filter = L"CSV файлы (*.csv)|*.csv|Все файлы (*.*)|*.*";
            dialog->Title = L"Открыть файл с данными";

            if (dialog->ShowDialog(this) == System::Windows::Forms::DialogResult::OK) {
                try {
                    String^ fileName = dialog->FileName;
                    std::string filePath = msclr::interop::marshal_as<std::string>(fileName);

                    hotel->clearRooms();

                    std::ifstream file(filePath);
                    if (!file.is_open()) {
                        MessageBox::Show(L"Ошибка открытия файла!",
                            L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
                        return;
                    }

                    std::string line;
                    while (std::getline(file, line)) {
                        if (line.empty()) continue;

                        std::stringstream ss(line);
                        std::string token;
                        std::vector<std::string> tokens;

                        while (std::getline(ss, token, ';')) {
                            tokens.push_back(token);
                        }

                        if (tokens.size() < 5) continue;

                        try {
                            int roomNumber = std::stoi(tokens[0]);
                            std::string roomType = tokens[1];
                            double basePrice = std::stod(tokens[2]);
                            std::string discountType = tokens[3];
                            double discountPercent = std::stod(tokens[4]);

                            std::unique_ptr<PricingStrategy> strategy;
                            if (discountType == "Без скидки") {
                                strategy = std::make_unique<NoDiscount>();
                            }
                            else {
                                strategy = std::make_unique<PercentageDiscount>(discountPercent);
                            }

                            Room* room = nullptr;
                            if (roomType == "Standard") {
                                room = new StandardRoom(roomNumber, basePrice, std::move(strategy));
                            }
                            else if (roomType == "Luxury") {
                                room = new LuxuryRoom(roomNumber, basePrice, std::move(strategy));
                            }

                            if (room) {
                                hotel->addRoom(room);
                            }
                        }
                        catch (const std::exception&) {
                            continue;
                        }
                    }

                    file.close();
                    RefreshGrid();
                    MessageBox::Show(L"Данные успешно загружены!",
                        L"Успешно", MessageBoxButtons::OK, MessageBoxIcon::Information);
                }
                catch (const std::exception& ex) {
                    String^ errorMsg = gcnew String(ex.what());
                    MessageBox::Show(L"Ошибка при загрузке: " + errorMsg,
                        L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
                }
            }
        }

        System::Void buttonSave_Click(System::Object^ sender, System::EventArgs^ e)
        {
            SaveFileDialog^ dialog = gcnew SaveFileDialog();
            dialog->Filter = L"CSV файлы (*.csv)|*.csv|Все файлы (*.*)|*.*";
            dialog->Title = L"Сохранить файл с данными";
            dialog->DefaultExt = L"csv";

            if (dialog->ShowDialog(this) == System::Windows::Forms::DialogResult::OK) {
                try {
                    String^ fileName = dialog->FileName;
                    std::string filePath = msclr::interop::marshal_as<std::string>(fileName);

                    std::ofstream file(filePath);
                    if (!file.is_open()) {
                        MessageBox::Show(L"Ошибка создания файла!",
                            L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
                        return;
                    }

                    const std::vector<Room*>& rooms = hotel->getRooms();
                    for (const auto& room : rooms) {
                        file << room->getRoomNumber() << ";";

                        std::string type = room->getRoomType();
                        file << type << ";";

                        StandardRoom* stdRoom = dynamic_cast<StandardRoom*>(room);
                        file << (stdRoom ? "Standard" : "Luxury") << ";";

                        file << std::fixed << std::setprecision(2) << room->getBasePrice() << ";";

                        if (room->hasNoDiscount()) {
                            file << "Без скидки;0.0\n";
                        }
                        else {
                            file << "Процентная;"
                                << std::fixed << std::setprecision(2)
                                << room->getDiscountPercentage() << "\n";
                        }
                    }

                    file.close();
                    MessageBox::Show(L"Данные успешно сохранены!",
                        L"Успешно", MessageBoxButtons::OK, MessageBoxIcon::Information);
                }
                catch (const std::exception& ex) {
                    String^ errorMsg = gcnew String(ex.what());
                    MessageBox::Show(L"Ошибка при сохранении: " + errorMsg,
                        L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
                }
            }
        }

        System::Void buttonSortNumber_Click(System::Object^ sender, System::EventArgs^ e)
        {
            hotel->sortByRoomNumber(sortNumberAscending);
            sortNumberAscending = !sortNumberAscending;
            UpdateSortButtonText();
            RefreshGrid();
        }

        System::Void buttonSortBasePrice_Click(System::Object^ sender, System::EventArgs^ e)
        {
            hotel->sortByBasePrice(sortBasePriceAscending);
            sortBasePriceAscending = !sortBasePriceAscending;
            UpdateSortButtonText();
            RefreshGrid();
        }

        System::Void buttonSortFinalPrice_Click(System::Object^ sender, System::EventArgs^ e)
        {
            hotel->sortByFinalPrice(sortFinalPriceAscending);
            sortFinalPriceAscending = !sortFinalPriceAscending;
            UpdateSortButtonText();
            RefreshGrid();
        }
    };

}

#include <iostream>
#include "iomanip"
#include "fstream"
//#define conditionCount 50000
using namespace std;

//cau truc thong tin sinh vien
struct HocSinh{
	int mahs;
	string ten;
	int gioitinh;
	int tuoi;
	float diemtb;
};
typedef struct HocSinh hocsinh;

void Column()
{
    cout << setw(15) << "Ma Hoc Sinh";
    cout << setw(15) << "Ten";
    cout << setw(15) << "Gioi Tinh";
    cout << setw(15) << "Tuoi";
    cout << setw(20) << "Diem Trung Binh";
    cout << endl;
}

//cau truc 1 node
struct node{
	hocsinh *data;
	struct node *next;
	struct node *prev;
	
};
typedef struct node Node;

//cau truc danh sach lien ket
struct list {
	Node* pHead;
};
typedef struct list List;

//nhap thong tin cho 1 sinh vien
void Input_ThongTin(hocsinh *hs) {
	cout << "Nhap Ma so hoc sinh(int) : ";
	cin >> hs->mahs;	
	cin.ignore();
	cout << "Nhap Ten hoc sinh(string) : ";
	fflush(stdin);
	getline(cin,hs->ten);
	cout << "gioi tinh(0 la nam, 1 la nu): ";
	cin>>hs->gioitinh;
	cout << "Nhap tuoi(int) : ";
	cin>>hs->tuoi;
	cout << "Diem trung binh(float) : ";
	cin>>hs->diemtb;
}

//khoi tao 1 node
Node *KhoiTaoNode() {
	hocsinh* hs = new hocsinh;
	Input_ThongTin(hs);
	Node* p = new Node;
	if (p == NULL) {
		cout << "full ram ko the tao thêm\n";
		return 0;
	}
	p->data = hs;
	p->next = NULL;
	p->prev = NULL;
	return p;
}


//them vao cuoi danh sach lien ket 1 node
void ThemVaoCuoiMotSinhVien(List &l, Node *p) {
	if (l.pHead == NULL) {
		l.pHead = p;
		l.pHead->next = l.pHead;
		l.pHead->prev = l.pHead;
		return;
	}
	else {
		Node *pTail = l.pHead->prev;
		p->next = l.pHead;
		p->prev = pTail;
		l.pHead->prev = p;
		pTail->next = p;
		pTail = p;
	}
}

//hien thi danh sach
void Show(List l){
	if (l.pHead == NULL ){
		cout<<"Danh sach trong !!\n\n";
		return;
	}
	Node *k = l.pHead;
	Column();
	do{
		cout << setw(15)<< k->data->mahs;
		cout << setw(15) << k->data->ten;
		cout <<setw(15); if(k->data->gioitinh == 1){
			cout<<"Nu";
		}
		else if (k->data->gioitinh == 0){
			cout<<"Nam";
		}
		else{
			cout<<"Undefine";
		};
		cout << setw(15) << k->data->tuoi;
		cout << setw(15) << k->data->diemtb<<endl;
		if(k->next != NULL){
			k = k->next;
		}
	}while(k != l.pHead);
}

//hien thi 1 node
void showNode(Node *k) {
	cout << setw(15)<< k->data->mahs;
	cout << setw(15) << k->data->ten;
	cout <<setw(15); 
	if(k->data->gioitinh == 1){
		cout<<"Nu";
	}
	else if (k->data->gioitinh == 0){
		cout<<"Nam";
	}
	else{
		cout<<"Undefine";
	};
	cout << setw(15) << k->data->tuoi;
	cout << setw(15) << k->data->diemtb<<endl;
}

//danh sach hoc sinh nu
void DsGioiTinhNu(List l){
	if (l.pHead == NULL ){
		cout<<"\nChua co du lieu !!\n\n";
		return;
	}
	if(l.pHead->next == l.pHead){
		if(l.pHead->data->gioitinh == 1){
			showNode(l.pHead);
		}
	}
	if(l.pHead->next != l.pHead){
		Node *k = l.pHead;
		Column();
		do{
			if(k->data->gioitinh == 1){
				showNode(k);
				k = k->next;
			}
			else{
				k = k->next;
			}
		}while(k != l.pHead);
	}
}

int soDiem8(List l){
	int soluongdiem = 0;
	if (l.pHead == NULL ) return soluongdiem;
	if(l.pHead->next == l.pHead){
		if(l.pHead->data->diemtb > 8.0){
			return 1;
		}
		else{
			return soluongdiem;
		}
	}
	if(l.pHead->next != l.pHead){
		Node *k = l.pHead;
		do{
			if(k->data->diemtb > 8.0){
				soluongdiem++;
				k = k->next;
			}
			else{
				k = k->next;
			}
		}while(k != l.pHead);

	}
	return soluongdiem;
}

//tim kiem 1 node
void search(List l ) {
	if(l.pHead == NULL){
		cout<<"\nDanh sach trong\n\n";
	}
	else{
		int  mshs;
		cout << "Nhap Ma So Hoc Sinh Can Tim Kiem : ";
		cin >> mshs;
		for (Node* k = l.pHead; k != NULL; k = k->next) {
			if (k->data->mahs == mshs) {
				cout<<"\nDA TIM THAY HOC SINH \n";
				Column();
				showNode(k);
				break;
			}
			if(k->data->mahs != mshs && k == l.pHead->prev){
				cout<<"\nKHONG TIM THAY HOC SINH\n";
				break;
			}
		}
	}
}

//xoa node dau tien
void deleteFirst(List &l){
	delete l.pHead;
	l.pHead = NULL;
}

//xoa 1 node bat ky
void deleteNode(List &l){
	int mshs;
	cout<<"Nhap Ma Hoc Sinh Can Xoa: ";
	cin>>mshs;
	
	if(l.pHead == NULL){//danh sach trong 
		return;
	}
	if(l.pHead->next == l.pHead){
		deleteFirst(l);
		cout<<"\nDa xoa hoc sinh \n\n";
	}
	else{//danh sach ton tai phan tu
		Node *left, *right;
		for (Node* k = l.pHead; k != NULL; k = k->next) {
			if (k->data->mahs == mshs && k == l.pHead) {
				cout<<"\nDa xoa hoc sinh \n\n";
				left = k->prev;
				right = k->next;
				left->next = right;
				right->prev = left;
				l.pHead = right;
				delete k;
				k = NULL;
				break;
			}
			else if(k->data->mahs == mshs && k != l.pHead){
				left = k->prev;
				right = k->next;
				left->next = right;
				right->prev = left;
				delete k;
				k = NULL;
				cout<<"\nDa xoa hoc sinh \n\n";
				break;
			}
		}
	}
}


//Sap xep danh sach
void SapXep(List &l){// Bubble Sort
	if(l.pHead == NULL){
		return;
	}
	Node *p, *q, *pTail;
	pTail = l.pHead->prev;
	for(p = l.pHead; p != pTail; p = p->next){
		for(q = p->next; q != l.pHead; q = q->next){
			if (p->data->diemtb > q->data->diemtb){
				swap(p->data, q->data);
			}
		}
	}

}

//Ham Doc file
void ReadFile(List &l){
    char fileName[30];
    fflush(stdin);
    cout << "Nhap ten file: ";
    cin.getline(fileName, 30);

    ifstream fileIn;
    fileIn.open(fileName);
    if (fileIn.fail()){
        cout << "Khong the mo file!!!";
        return;
    }

    while (!fileIn.eof()){
    	hocsinh* hs = new hocsinh;
        fileIn >> hs->mahs;
        fileIn >> hs->ten;
        fileIn >> hs->gioitinh;
        fileIn >> hs->tuoi;
        fileIn >> hs->diemtb;
        Node* p = new Node;
        if (p == NULL) {
		cout << "full ram ko the tao thêm\n";
		}
		p->data = hs;
		p->next = NULL;
		p->prev = NULL;
        ThemVaoCuoiMotSinhVien(l, p);
    }
    fileIn.close();
    cout << "Doc du lieu tu file thanh cong!!!\n";
    system("pause");
}

// Ham ghi file thanh text
void WriteFile(List &l)
{
    char fileName[20];
    fflush(stdin);
    cout << "\nNhap ten file muon luu: ";
    cin.getline(fileName, 20);

    Node *k = l.pHead;
    ofstream fileOut;
    fileOut.open(fileName);
    while (l.pHead != NULL)
    {
        fileOut << k->data->mahs << " ";
        fileOut << k->data->ten << " ";
        fileOut << k->data->gioitinh << " ";
        fileOut << k->data->tuoi << " ";
        fileOut << k->data->diemtb << endl; 
        k = k->next;
        if(k == l.pHead){
        	break;
		}
    }
    fileOut.close();
    cout<<"Luu file thanh cong"<<endl;
    system("pause");
}
//Menu chuc nang
void Menu(List &l) {
	int choice;
  	do{
  		system("cls");
  		cout << "\n\n\t HOANG DAC HUNG";
  		cout << "\n\n\t MSV: 18103200013";
  		cout << "\n\n\t =======DANH SACH LIEN KET DOI VONG=======";
        cout << "\n\n\t ================ MENU ===================";
        cout << "\n\t 1. In Danh sach";
        cout << "\n\t 2. Tim kiem hoc sinh(theo ma hoc sinh)";
		cout << "\n\t 3. Them thong tin 1 hoc sinh";
		cout << "\n\t 4. Xoa thong tin 1 hoc sinh";
		cout << "\n\t 5. In danh sach hoc sinh nu";
		cout << "\n\t 6. So hoc sinh co diem trung binh > 8.0";
		cout << "\n\t 7. Sap xep danh sach tang dan theo diem tb";
		cout << "\n\t 8. Chen 1 hoc sinh van thoa man dieu kien tang dan diem tb";
		cout << "\n\t 9. Nhap du lieu tu file";
		cout << "\n\t 10. Luu danh sach thanh file text";
        cout << "\n\t =================== END ====================";
    	
		cout<<"\nNhap lua chon: ";
        cin>> choice;
        switch(choice){
            case 0:{ 
				break;
			}
            case 1:{
				cout << "\n\n DANH SACH HOC SINH \n\n";
				Show(l);
				system("pause");
	            break;
	    	}
	    	case 2:{
				search(l);
				system("pause");
	            break;
	    	}
            case 3:{
	            cout << "Moi Ban nhap thong tin 1 hoc sinh : \n";
				Node* p = KhoiTaoNode();
				ThemVaoCuoiMotSinhVien(l, p);
				system("pause");
	            break;
	        }
	        case 4:{
	        	deleteNode(l);
	        	system("pause");
				break;
			}
			case 5:{
				cout<<"\nDANH SACH HOC SINH NU\n";
				DsGioiTinhNu(l);
				system("pause");
				break;
			}
			case 6:{
				int diem = soDiem8(l);
				cout<<"So hoc sinh co so diem trung binh > 8.0 la: "<<diem<<"\n";
				system("pause");
				break;
			}
			case 7:{
				Show(l);
				SapXep(l);
				cout<<"\n\n                ========DANH SACH SAU KHI SAP XEP========            \n";
				Show(l);
				system("pause");
				break;
			}
			case 8:{
				cout << "Moi Ban nhap thong tin 1 hoc sinh : \n";
				Node* p = KhoiTaoNode();
				ThemVaoCuoiMotSinhVien(l, p);
				SapXep(l);
				system("pause");
	            break;
			}
			case 9:{
				ReadFile(l);
				break;
			}
			case 10:{
				WriteFile(l);
				break;
			}
            default:{ 
				cout<<"\nNhap sai, vui long nhap lai!";
			}
        }
    } while(choice);
}

int main(){
	List l;
	Menu(l);
	system("pause");
	return 0;
}

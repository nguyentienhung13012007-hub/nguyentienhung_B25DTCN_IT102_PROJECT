#include <stdio.h>
#include <string.h>
#define MAX 50
#define PAGE_SIZE 10

typedef struct {
    char roomId[5];
    int type;
    double price;
    int status;   // 0 - trong, 1 - dã thuê, 2 - bao trì
} Room;

typedef struct {
    char bookId[20];
    char roomId[5];
    char customerName[50];
    int days;
    double totalCost;
} Booking;

// ===== BIeN TOaN CuC =====
Room ds[MAX];
int soPhong = 0;

// ================= THÊM PHÒNG =================
void addRoom() {
    Room newRoom;

    printf("Nhap so phong: ");
    fflush(stdin);
    scanf("%s", newRoom.roomId);
//kiem tra so phong khong duoc de trong  
    if (strlen(newRoom.roomId) == 0) {
        printf("Loi: So phong khong duoc de trong!\n");
        return;
    }
//kiemm tra xem phong da ton tai chua 
    for (int i = 0; i < soPhong; i++) {

        if (strcmp(ds[i].roomId, newRoom.roomId) == 0) {
            printf("Loi: Phong %s da ton tai!\n", newRoom.roomId);
            return;
        }
    }
do{
	printf("Nhap loai phong (1: Don, 2: Doi): ");
    scanf("%d", &newRoom.type);
//kiem tra loai phong co hop le  khong  
    if (newRoom.type != 1 && newRoom.type != 2) {
        printf("Loi: Loai phong chi duoc chon 1 hoac 2!\n");
       
    }

}while(newRoom.type != 1 && newRoom.type != 2);
    
    do {
        printf("Nhap gia phong: ");
        scanf("%lf", &newRoom.price);
//kiem tra gia phong phai duong  
        if (newRoom.price <= 0)
            printf("Gia phong phai lon hon 0!\n");

    } while (newRoom.price <= 0);
    

printf("Trang thai phong (0:Trong ;1: Dang o;2: Bao tri) :0 \n");
 
//tang so phong len them 1  
    ds[soPhong++] = newRoom;
    printf("Them phong thanh cong!Phong %s da duoc tao voi trang thai Trong.\n",newRoom.roomId);
}

// ================= CaP NHaT PHÒNG =================
void updateRoom() {
    char id[5];
    printf("Nhap so phong can cap nhat: ");
    fflush(stdin);
    scanf("%s", id);
    //kiem tra so phong can cap nhat co  ton tai khong  
    for (int i = 0; i < soPhong; i++) {
    	
   	//kiem tra phong khong dc de trong  
        if (strcmp(ds[i].roomId, id) == 0) {
        //nhap den khi nao thoa man  loai phong 
		do{
		
            printf("Loai phong hien tai: %d . Nhap loai phong moi ( 1: Don, 2: Doi): ",ds[i].type);
            scanf("%d", &ds[i].type);
            
        if (ds[i].type != 1 && ds[i].type != 2) {
        printf("Loi: Loai phong chi duoc chon 1 hoac 2!\n");
      
        }
     }while(ds[i].type != 1 && ds[i].type != 2);
    //nhap den khi nao thoa man gia phong >0  
       do {
        printf("Gia phong hien tai: %lf . Nhap gia phong moi: ",ds[i].price);
        scanf("%lf", &ds[i].price);

        if (ds[i].price <= 0)
            printf("Gia phong phai lon hon 0!\n");

     } while (ds[i].price <= 0);
     
     
         do{
   	  printf("Nhap trang thai phong moi  (0:Trong ;1: Dang o;2: Bao tri): ");
   	  scanf("%d",&ds[i].status);
   	  if(ds[i].status<0&&ds[i].status>2){
   	  	printf("Loi!Nhap lai trang thai phong");
		 }
	}while(ds[i].status<0&&ds[i].status>2);


            printf("Cap nhat thong tin phong %s thanh cong!\n",id);
            return;
        }
    }

    printf("Khong tim thay phong %s!\n",id);
}
//===========bao tri =======             
void lockRoom() {
    char id[5];
    printf("Nhap so phong can bao tri: ");
    scanf("%s", id);

    for (int i = 0; i < soPhong; i++) {
        if (strcmp(ds[i].roomId, id) == 0) {
//neu co khach thi khong bao tri 
            if (ds[i].status == 1) {
                printf("Loi: Phong %s dang co khach, khong the dua vao bao tri!\n", id);
                return;
            }

            // neu phong da bao tri
            if (ds[i].status == 2) {
                printf("Phong %s da o trang thai bao tri!\n", id);
                return;
            }

           //neu trong thi bao tri
            ds[i].status = 2;
            printf("Da dua phong %s vao trang thai Bao tri thanh cong \n", id);
            return;
        }
    }

    printf("Loi! Khong tim thay phong %s!\n", id);
}

///=======================Hien thi danh sach (trang)======================
void displayPage(int page) {
    int start = page * PAGE_SIZE;
    int end = start + PAGE_SIZE;
    if (start >= soPhong) {
        printf("Trang khong ton tai.\n");
        return;
    }
    if (end > soPhong) end = soPhong;

    printf("\n================== TRANG %d ==================\n", page + 1);
    printf("%-4s %-8s %-8s %-12s %-12s\n", "STT", "RoomId", "Type", "Price", "Status");
    for (int i = start; i < end; i++) {
        char *typeStr = (ds[i].type == 1) ? "Don" : "Doi";
        char *statusStr = (ds[i].status == 0) ? "Trong" : (ds[i].status == 1) ? "Dang o" : "Bao tri";
        printf("%-4d %-8s %-8s %-12.2lf %-12s\n", i+1, ds[i].roomId, typeStr, ds[i].price, statusStr);
    }
    printf("=============================================\n");
}

void displayRooms() {
    if (soPhong == 0) {
        printf(">>> Danh sach khong co phong nao.\n");
        return;
    }
    int totalPages = (soPhong + PAGE_SIZE - 1) / PAGE_SIZE;
    int page = 0;
    while (1) {
        displayPage(page);
        if (page + 1 >= totalPages) {
            printf("End of list. Nh?n Enter de tro ve menu...");
            getchar();
            break;
        } else {
            printf("Nhap N de trang ke tiep, P de trang truoc, Q de thoat xem: ");
            char c = getchar();
            while (getchar() != '\n'); // flush rest
            if (c == 'N' || c == 'n') {
                page++;
            } else if (c == 'P' || c == 'p') {
                if (page > 0) page--;
            } else {
                break;
            }
        }
    }
}
int main (){
	int choose;
	while(1){
		printf("|==============Quan ly khach san===================|\n");
		printf("|  1.Them phong moi                                |\n");
		printf("|  2.Cap nhat phong                                |\n");
		printf("|  3.Bao tri phong                                 |\n");
		printf("|  4.Hien thi  danh sach                           |\n");
		printf("|  5. Tim kiem                                     |\n");
		printf("|  6. Sap xep danh sach phong(theo gia )           |\n");
		printf("|  7 .Check-in                                     |\n");
		printf("|  8.Lich su thue                                  |\n");
		printf("|==================================================|\n");
		printf(" \nMoi ban chon chuc nang:   ");
		scanf("%d",&choose);
		switch(choose){
			case 1:{
				addRoom();
				break;
			}
			case 2:{
				updateRoom();
				break;
			}
			case 3:{
				lockRoom();
				break;
			}
			case 4:{
				displayRooms();
				break;
			}
//			case 5:
//			case 6:
//			case 7:
//			case 8:
			
		}
	}
}



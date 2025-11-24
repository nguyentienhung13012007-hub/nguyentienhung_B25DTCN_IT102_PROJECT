#include <stdio.h>
#include <string.h>
#define MAX 50


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

    if (strlen(newRoom.roomId) == 0) {
        printf("Loi: So phong khong duoc de trong!\n");
        return;
    }

    for (int i = 0; i < soPhong; i++) {
        if (strcmp(ds[i].roomId, newRoom.roomId) == 0) {
            printf("Loi: Phong %s da ton tai!\n", newRoom.roomId);
            return;
        }
    }

    printf("Nhap loai phong (1: Don, 2: Doi): ");
    scanf("%d", &newRoom.type);

    if (newRoom.type != 1 && newRoom.type != 2) {
        printf("Loi: Loai phong chi duoc chon 1 hoac 2!\n");
        return;
    }

    do {
        printf("Nhap gia phong: ");
        scanf("%lf", &newRoom.price);

        if (newRoom.price <= 0)
            printf("Gia phong phai lon hon 0!\n");

    } while (newRoom.price <= 0);

   

    ds[soPhong++] = newRoom;
    printf(">>> Them phong thanh cong!Phong %s da duoc tao voi trang thai Trong.\n",newRoom.roomId);
}

// ================= CaP NHaT PHÒNG =================
void updateRoom() {
    char id[5];
    printf("Nhap so phong can cap nhat: ");
    fflush(stdin);
    scanf("%s", id);
    for (int i = 0; i < soPhong; i++) {
    	
   	
        if (strcmp(ds[i].roomId, id) == 0) {
        do{
		
            printf("Nhap loai phong moi ( 1: Don, 2: Doi): ");
            scanf("%d", &ds[i].type);
            
        if (ds[i].type != 1 && ds[i].type != 2) {
        printf("Loi: Loai phong chi duoc chon 1 hoac 2!\n");
      
    }
}while(ds[i].type != 1 && ds[i].type != 2);
    
    do {
        printf("Nhap gia phong moi: ");
        scanf("%lf", &ds[i].price);

        if (ds[i].price <= 0)
            printf("Gia phong phai lon hon 0!\n");

    } while (ds[i].price <= 0);


            printf(">>> Cap nhat thong tin phong %s thanh cong!\n",id);
            return;
        }
    }

    printf("Khong tim thay phong %s!\n",id);
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
//			}
//			case 3:
//			case 4:
//			case 5:
//			case 6:
//			case 7:
//			case 8:
			
		}
	}
}
}


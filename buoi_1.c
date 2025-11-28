#include <stdio.h>
#include <string.h>
#include <math.h>
#define MAX 50
#define PAGE_SIZE 5

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
    char checkInDate[15];

    
} Booking;

// ===== BIeN TOaN CuC =====
Room dss [MAX];     
int soPhong = 0;

Booking ds[MAX];
int soPhongg = 0;


//=====confirm xoa man hinh====
int confirmClear() {
    char ch;
    printf("\nBan co muon xoa man hinh? (y/n): ");
    fflush(stdin);
    scanf(" %c", &ch);

    if(ch == 'y' || ch == 'Y') {
        system("cls"); // xóa màn hình neu YES
        return 1;
    }
    return 0; // không xóa neu NO
}

// ================= THÊM PHÒNG =================
void addRoom() {
    if (soPhong >= MAX) {
        printf(">>> Khong the them phong moi. Danh sach da day (%d phong).\n", MAX);
        return;
    }

    Room newRoom;

    // Nhap RoomID
    while (1) {
        printf("Nhap so phong: ");
        fflush(stdin);
        fgets(newRoom.roomId, sizeof(newRoom.roomId), stdin);

        // Loai bo '\n' neu co
        size_t len = strlen(newRoom.roomId);
        if (len > 0 && newRoom.roomId[len - 1] == '\n')
            newRoom.roomId[len - 1] = '\0';

        // Kiem tra rong
        if (strlen(newRoom.roomId) == 0) {
            printf("Loi: So phong khong duoc de trong!\n");
            continue;
        }

        // Kiem tra phong da ton tai
        int exists = 0;
        for (int i = 0; i < soPhong; i++) {
            if (strcmp(ds[i].roomId, newRoom.roomId) == 0) {
                printf("Loi: Phong %s da ton tai!\n", newRoom.roomId);
                exists = 1;
                break;
            }
        }
        if (!exists) break; // khong trung -> thoat vong lap
    }

    // Nhap type
    do {
        printf("Nhap loai phong (1: Don, 2: Doi): ");
        scanf("%d", &newRoom.type);
        if (newRoom.type != 1 && newRoom.type != 2)
            printf("Loi: Loai phong chi duoc chon 1 hoac 2!\n");
    } while (newRoom.type != 1 && newRoom.type != 2);

    // Nhap gia phong
    do {
        printf("Nhap gia phong: ");
        scanf("%lf", &newRoom.price);
        if (newRoom.price <= 0)
            printf("Gia phong phai lon hon 0!\n");
    } while (newRoom.price <= 0);

    newRoom.status = 0; // mac dinh Trong
    dss[soPhong++] = newRoom;

    printf("Them phong thanh cong! Phong %s da duoc tao voi trang thai Trong.\n", newRoom.roomId);
confirmClear();

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
        if (strcmp(dss[i].roomId, id) == 0) {
        //nhap den khi nao thoa man  loai phong 
		do{
		
            printf("Loai phong hien tai: %d . Nhap loai phong moi ( 1: Don, 2: Doi): ",dss[i].type);
            scanf("%d", &dss[i].type);
            
        if (dss[i].type != 1 && dss[i].type != 2) {
        printf("Loi: Loai phong chi duoc chon 1 hoac 2!\n");
      
        }
     }while(dss[i].type != 1 && dss[i].type != 2);
    //nhap den khi nao thoa man gia phong >0  
       do {
        printf("Gia phong hien tai: %lf . Nhap gia phong moi: ",dss[i].price);
        scanf("%lf", &dss[i].price);

        if (dss[i].price <= 0)
            printf("Gia phong phai lon hon 0!\n");

     } while (dss[i].price <= 0);
     
     
         do{
   	  printf("Nhap trang thai phong moi  (0:Trong ;1: Dang o;2: Bao tri): ");
   	  scanf("%d",&dss[i].status);
   	  if(dss[i].status<0&&dss[i].status>2){
   	  	printf("Loi!Nhap lai trang thai phong");
		 }
	}while(dss[i].status<0||dss[i].status>2);


            printf("Cap nhat thong tin phong %s thanh cong!\n",id);
            return;
        }
    }

    printf("Khong tim thay phong %s!\n",id);
    confirmClear();

}
//===========bao tri =======             
void lockRoom() {
    char id[5];
    printf("Nhap so phong can bao tri: ");
    scanf("%s", id);

    for (int i = 0; i < soPhong; i++) {
        if (strcmp(dss[i].roomId, id) == 0) {
//neu co khach thi khong bao tri 
            if (dss[i].status == 1) {
                printf("Loi: Phong %s dang co khach, khong the dua vao bao tri!\n", id);
                return;
            }

            // neu phong da bao tri
            if (dss[i].status == 2) {
                printf("Phong %s da o trang thai bao tri!\n", id);
                return;
            }

           //neu trong thi bao tri
            dss[i].status = 2;
            printf("Da dua phong %s vao trang thai Bao tri thanh cong \n", id);
            return;
        }
    }

    printf("Loi! Khong tim thay phong %s!\n", id);
    confirmClear();

}

///=======================Hien thi danh sach (trang)======================
void displayRooms() {
    if (soPhong == 0) {
        printf("\n>>> Danh sach phong hien tai TRONG! Vui long them phong truoc.\n");
        return;
    }

    int totalPage = (soPhong + PAGE_SIZE - 1) / PAGE_SIZE;
    int page = 1;
    char input[10];

    while (1) {
        int start = (page - 1) * PAGE_SIZE;
        int end = start + PAGE_SIZE;
        if (end > soPhong) end = soPhong;

        printf("\n================ DANH SACH PHONG (Trang %d/%d) ================\n", page, totalPage);
        printf("|%-5s |%-10s |%-8s |%-10s |%-12s|\n", "STT", "RoomID", "Loai", "Gia", "Trang Thai");
        printf("---------------------------------------------------------------------\n");

        for (int i = start; i < end; i++) {
            char typeStr[10];
            char statusStr[15];

            // Ðoi type sang chu
            if (dss[i].type == 1)
                strcpy(typeStr, "Don");
            else
                strcpy(typeStr, "Doi");

            // Ðoi status sang chu
            if (dss[i].status == 0)
                strcpy(statusStr, "Trong");
            else if (dss[i].status == 1)
                strcpy(statusStr, "Dang o");
            else
                strcpy(statusStr, "Bao tri");

            printf("|%-5d |%-10s |%-8s |%-10.2lf |%-12s|\n",
                   i + 1, dss[i].roomId, typeStr, dss[i].price, statusStr);
        }

        printf("---------------------------------------------------------------------\n");

        if (page == totalPage) {
            printf(">>> Da o trang cuoi. Nhan Enter de thoat.");
            getchar(); // clear buffer
            fgets(input, sizeof(input), stdin);
            break;
        }

        printf("Nhap so trang muon den (1-%d), hoac Enter de sang trang tiep: ", totalPage);
        getchar(); 
        fgets(input, sizeof(input), stdin);

        // Nguoi dùng nhan Enter -> sang trang tiep theo
        if (input[0] == '\n') {
            page++;
            continue;
        }

        // Nguoi dùng nhap so trang
        int newPage = atoi(input);
        if (newPage >= 1 && newPage <= totalPage) {
            page = newPage;
        } else {
            printf("Trang khong hop le!\n");
        }
    }
    confirmClear();

}

//===========tim phong theo loai==============
void findRoom(){
	int type;
	do{
	printf("Nhap loai phong (1: Don, 2: Doi): ");
    scanf("%d", &type);
//kiem tra loai phong co hop le  khong  
    if (type != 1 && type != 2) {
        printf("Loi: Loai phong chi duoc chon 1 hoac 2!\n");
    }
	}while(type != 1 && type != 2);

	int find =0;
	printf("Phong trong loai %d: \n",type);
    printf("|%-4s |%-8s |%-8s |%-12s|\n", "STT", "RoomId", "Type", "Price");
    for (int i = 0; i < soPhong; i++) {
        if (dss[i].type == type && dss[i].status == 0) {
            find++;
            printf("|%-4d |%-8s |%-8d |%-12.2lf|\n", find, dss[i].roomId, dss[i].type, dss[i].price);
        }
    }
    if (!find) printf("Hien tai khong co phong trong loai %d.\n",type);
confirmClear();

}
//==============sap xep lai gian dan theo gia=========
void searchRoom(){
	if(soPhong==0){
		printf("Danh sach phong trong,khong can sap xep!\n");
		confirmClear();
		return ;
	}
	
	//===bubble sort giam dan theo gia
	
	for(int i=0;i<soPhong-1;i++){
		for(int j=i+1;j<soPhong;j++){
			if(dss[i].price<dss[j].price){
				Room temp=dss[i];
				dss[i]=dss[j];
				dss[j]= temp;
				
			}
		
		}
		
	}
	printf("===Danh sach phong (Gia giam dan)===\n");
	printf("|%5s|%-10s |%-8s |%-10s |%-12s|\n","STT","RoomId","Type","Price","Status");
	printf("---------------------------------------------------------------------\n");
	
	    for (int i = 0; i < soPhong; i++) {

        char typeStr[10], statusStr[15];
        strcpy(typeStr, (dss[i].type == 1) ? "Don" : "Doi");
        strcpy(statusStr,
               (dss[i].status == 0) ? "Trong" :
               (dss[i].status == 1) ? "Dang o" :
                                     "Bao tri");

        printf("|%-5d |%-10s |%-8s |%-10.2lf |%-12s|\n",
               i + 1, dss[i].roomId, typeStr, dss[i].price, statusStr);
    }

	printf("Da sap xep danh sach phong theo gia giam dan thanh cong!\n");
confirmClear();

}

//=ham kiem tra dinh dang ngay 
int isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int isValidDate(char *date) {
    if (strlen(date) != 10) return 0;            // DD/MM/YYYY
    if (date[2] != '/' || date[5] != '/') return 0;

    int d = (date[0]-'0')*10 + (date[1]-'0');
    int m = (date[3]-'0')*10 + (date[4]-'0');
    int y = atoi(date+6);

    if (y < 1900) return 0;                     // nam hop le
    if (m < 1 || m > 12) return 0;              // tháng hop le

    int maxDay;
    switch(m) {
        case 2:
            maxDay = isLeapYear(y) ? 29 : 28;
            break;
        case 4: case 6: case 9: case 11:
            maxDay = 30;
            break;
        default:
            maxDay = 31;
    }

    if (d < 1 || d > maxDay) return 0;          // ngày hop le theo thang
    return 1;
}


//ham tao ma booking
void generateBookId(char *id, int index) {
    sprintf(id, "BK%03d", index + 1);
}
 
//=======check in booking=========

void checkIn() {
    char roomId[5], cusName[50], date[15];
    int days;

    printf("Nhap so phong: ");
    scanf("%s", roomId);

    // 1. Tim phong
    int pos = -1;
    for (int i = 0; i < soPhong; i++) {
        if (strcmp(dss[i].roomId, roomId) == 0) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("Loi: Khong tim thay phong %s!\n", roomId);
        return;
    }

    // 2. Kiem tra trang thai
    if (dss[pos].status == 1) {
        printf("Loi: Phong %s da co khach!\n", roomId);
        return;
    }
    if (dss[pos].status == 2) {
        printf("Loi: Phong %s dang bao tri!\n", roomId);
        return;
    }

    // 3. Nhap ten khach
    printf("Nhap ten khach hang: ");
    fflush(stdin);
    fgets(cusName, sizeof(cusName), stdin);
    cusName[strcspn(cusName, "\n")] = 0;

    // 4. Nhap so ngay

do {
    printf("Nhap so ngay o: ");
    scanf("%d", &days);

    if (days <= 0) {
        printf("Loi: So ngay o phai lon hon 0!\n");
    }
} while (days <= 0);

// 5. Nhap ngày nhan phòng
do {
    printf("Nhap ngay nhan phong (DD/MM/YYYY): ");
    scanf("%s", date);

    if (!isValidDate(date)) {
        printf("Loi: Ngay nhan phong phai dung dinh dang DD/MM/YYYY!\n");
    }
} while (!isValidDate(date));


    // === Tao booking moi ===
    Booking b;
    strcpy(b.roomId, roomId);
    strcpy(b.customerName, cusName);
    strcpy(b.checkInDate, date);

    b.days = days;
    b.totalCost = dss[pos].price * days;

    generateBookId(b.bookId, soPhongg);

    ds[soPhongg] = b;
    soPhongg++;

    // Ðoi trang thai phong
    dss[pos].status = 1;

    // In hoa don
    printf("\nCheck-in thanh cong! Ma dat phong: %s\n", b.bookId);

    printf("\n===== HOA DON CHECK-IN =====\n");
    printf("Ma dat phong : %s\n", b.bookId);
    printf("Phong        : %s\n", b.roomId);
    printf("Khach hang   : %s\n", b.customerName);
    printf("Ngay nhan    : %s\n", b.checkInDate);
    printf("So ngay o    : %d\n", b.days);
    printf("Tong tien    : %.2lf\n", b.totalCost);
    printf("====================================\n");
}

// F08 - Lich su thue phong
void history(Room rooms[], int soPhong, Booking bookings[], int soBooking) {
    char roomId[10];
    printf("Nhap so phong can xem lich su: ");
    fflush(stdin);
    scanf("%s", roomId);

    // 1. Kiem tra roomId ton tai
    int pos = -1;
    for (int i = 0; i < soPhong; i++) {
        if (strcmp(rooms[i].roomId, roomId) == 0) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("Loi: Khong tim thay phong %s!\n", roomId);
        return;
    }

    // 2. Tim lich su trong bookings
    int count = 0;

    for (int i = 0; i < soBooking; i++) {
        if (strcmp(bookings[i].roomId, roomId) == 0) {
            count++;
        }
    }

    if (count == 0) {
        printf("Phong %s chua tung co khach thue!\n", roomId);
        return;
    }

    // 3. In bang lich su chi tiet
    printf("\n===== LICH SU THUE PHONG %s =====\n", roomId);
    printf("%-4s %-10s %-20s %-12s %-6s %-10s\n",
           "STT", "BookID", "Khach Hang", "Check-in", "Days", "Total");

    int stt = 1;
    for (int i = 0; i < soBooking; i++) {
        if (strcmp(bookings[i].roomId, roomId) == 0) {
            printf("%-4d %-10s %-20s %-12s %-6d %-10.2lf\n",
                   stt++,
                   bookings[i].bookId,
                   bookings[i].customerName,
                   bookings[i].checkInDate,
                   bookings[i].days,
                   bookings[i].totalCost);
        }
    }
}



int main (){
	int choose;
	//gan co dinh du lieu 
    Room r1 = {"101", 1, 500000, 1};   // don - co khach
    Room r2 = {"102", 2, 600000, 0};   // doi - trong
    Room r3 = {"103", 1, 450000, 1};   // don - co khach
    Room r4 = {"104", 2, 700000, 2};   // doi - bao tri
    Room r5 = {"105", 1, 550000, 1};   // don - co khach
    Room r6 = {"106", 2, 500000, 1};
    Room r7 = {"107", 1, 750000, 1};
    Room r8 = {"108", 2, 1000000, 1};
    dss[0] = r1;
    dss[1] = r2;
    dss[2] = r3;
    dss[3] = r4;
    dss[4] = r5;
    dss[5] = r6;
    dss[6] = r7;
    dss[7] = r8;
    soPhong = 8;
	
	while(1){
		
		printf("|==============Quan ly khach san===================|\n");
		printf("|  1. Them phong moi                               |\n");
		printf("|  2. Cap nhat phong                               |\n");
		printf("|  3. Bao tri phong                                |\n");
		printf("|  4. Hien thi  danh sach                          |\n");
		printf("|  5. Tim kiem                                     |\n");
		printf("|  6. Sap xep danh sach phong(theo gia )           |\n");
		printf("|  7. Check-in                                     |\n");
		printf("|  8. Lich su thue                                 |\n");
	    printf("|  9. Thoat                                        |\n");
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
			case 5:{
				findRoom();
				break;
			}
			case 6:{
				searchRoom();
				break;
			}
			case 7:{
				checkIn();
				break;
			}
		case 8:{
			history(dss, soPhong, ds, soPhongg);

			break;
		}
		case 9:{
			printf("Exit!Bye,see you again.");
			return 0; 
			break;
		}	
		default:
			printf("Lua chon khong hop le.Vui long nhap lai! \n");
		}
	}
}



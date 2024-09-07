#ifndef _PACKET_H
#define _PACKET_H

///////////////////////////////////////////////////////////////////////////////
// HEADER
#define HEADER_LEN     8
#define SERVICE_HEADER "HEADER"
typedef struct {
    char length       [8  ];
    char service_name [8  ];
    char message      [128];
} HEADER;

///////////////////////////////////////////////////////////////////////////////
// LOGIN
#define SERVICE_LGIN001 "LGIN0001"
typedef struct {
    char user_id      [64 ];
    char user_pw      [256];
} LGIN0001_IB;

typedef struct {
    char result_yn    [1  ];
    char name         [64 ];
} LGIN0001_OB;

#endif // _PACKET_H

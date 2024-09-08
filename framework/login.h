#ifndef _LOGIN_H
#define _LOGIN_H

#include "../include/common.h"
#include "../include/define.h"
#include "../include/packet.h"

#include "../class/user.h"
#include "../class/util.h"
#include "../class/crypt.h"

#include "../interface/client.h"

// Menu
#define LOGIN_MENU	"##########################################################################\n" \
					"#                                                                        #\n" \
					"# login: 로그인 signup: 회원가입 find: 아이디 찾기 change: 비밀번호 변경 #\n" \
					"#                                                                        #\n" \
					"##########################################################################\n"
#define LOGIN_USER	"##########################################################################\n" \
					"#                                                                        #\n" \
					"#                              Tetris Login!                             #\n" \
					"#                                                                        #\n" \
					"##########################################################################\n"
#define MENU_LOGIN  101
#define MENU_SIGNUP 102
#define MENU_FIND   103
#define MENU_CHANGE 104


int login_proceduer(User& user);
int loginGetMenuDivision(std::string menu);
int userSignup(User& user, Client& client);
int userLogin(User& user, Client& client);
int requestLogin(Client& client);


#endif // _LOGIN_H

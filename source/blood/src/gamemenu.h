//-------------------------------------------------------------------------
/*
Copyright (C) 2010-2019 EDuke32 developers and contributors
Copyright (C) 2019 Nuke.YKT

This file is part of NBlood.

NBlood is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License version 2
as published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
//-------------------------------------------------------------------------
#pragma once

#include "compat.h"
#include "common_game.h"
#include "blood.h"
#include "inifile.h"
#include "resource.h"
#include "qav.h"

#define M_MOUSETIMEOUT 210

#define kMaxGameMenuItems 32
#define kMaxGameCycleItems 32
#define kMaxPicCycleItems 32

// alpha increments of 3 --> 255 / 3 = 85 --> round up to power of 2 --> 128 --> divide by 2 --> 64 alphatabs required
// use 16 anyway :P
#define MOUSEUSEALPHA (videoGetRenderMode() != REND_CLASSIC || numalphatabs >= 15)
#define MOUSEALPHA (MOUSEUSEALPHA ? clamp((totalclock - gGameMenuMgr.m_mouselastactivity - 90)*3, 0, 255) : 0)
#define CURSORALPHA (MOUSEUSEALPHA ? clamp((totalclock - gGameMenuMgr.m_mouselastactivity - 90)*2 + (255/3), (255/3), 255) : 255/3)
#define MOUSEACTIVECONDITION (totalclock - gGameMenuMgr.m_mouselastactivity < M_MOUSETIMEOUT)
#define MOUSEACTIVECONDITIONAL(condition) (MOUSEACTIVECONDITION && (condition))
#define MOUSEINACTIVECONDITIONAL(condition) (!MOUSEACTIVECONDITION && (condition))
#define MOUSEWATCHPOINTCONDITIONAL(condition) ((condition) || gGameMenuMgr.m_mousewake_watchpoint || gGameMenuMgr.m_menuchange_watchpoint == 3)

enum {
    kMenuEventNone = 0,
    kMenuEventKey = 1,
    kMenuEventUp = 2,
    kMenuEventDown = 3,
    kMenuEventLeft = 4,
    kMenuEventRight = 5,
    kMenuEventEnter = 6,
    kMenuEventEscape = 7,
    kMenuEventSpace = 8,
    kMenuEventBackSpace = 9,
    kMenuEventDelete = 10,
    kMenuEventScrollUp = 11,
    kMenuEventScrollDown = 12,


    kMenuEventInit = 0x8000,
    kMenuEventDeInit = 0x8001
};

struct CGameMenuEvent {
    unsigned short at0;
    char at2;
};

// NUKE-TODO:
#ifdef DrawText
#undef DrawText
#endif

class CMenuTextMgr
{
public:
    int at0;
    CMenuTextMgr();
    void DrawText(const char *pString, int nFont, int x, int y, int nShade, int nPalette, bool shadow );
    void GetFontInfo(int nFont, const char *pString, int *pXSize, int *pYSize);
};

class CGameMenu;

class CGameMenuItem {
public:
    CGameMenu *pMenu;
    const char* pzText;
    int nFont;
    int nX;
    int nY;
    int nWidth;
    int at18;
    CGameMenuItem();
    virtual void Draw(void) = 0;
    virtual bool Event(CGameMenuEvent &);
    virtual bool MouseEvent(CGameMenuEvent &);
};

class CGameMenuItemText : public CGameMenuItem
{
public:
    int at20;
    CGameMenuItemText();
    CGameMenuItemText(const char *, int, int, int, int);
    virtual void Draw(void);
    //virtual bool Event(CGameMenuEvent &);
};

class CGameMenuItemTitle : public CGameMenuItem
{
public:
    int at20;
    CGameMenuItemTitle();
    CGameMenuItemTitle(const char *, int, int, int, int);
    virtual void Draw(void);
    //virtual bool Event(CGameMenuEvent &);
};

class CGameMenuItemZBool : public CGameMenuItem
{
public:
    bool at20;
    const char *at21;
    const char *at25;
    void (*at29)(CGameMenuItemZBool *);
    CGameMenuItemZBool();
    CGameMenuItemZBool(const char *,int,int,int,int,bool,void (*)(CGameMenuItemZBool *),const char *,const char *);
    virtual void Draw(void);
    virtual bool Event(CGameMenuEvent &);
};

class CGameMenuItemChain : public CGameMenuItem
{
public:
    int at20;
    CGameMenu *at24;
    int at28;
    void(*at2c)(CGameMenuItemChain *);
    int at30;
    CGameMenuItemChain();
    CGameMenuItemChain(const char *, int, int, int, int, int, CGameMenu *, int, void(*)(CGameMenuItemChain *), int);
    virtual void Draw(void);
    virtual bool Event(CGameMenuEvent &);
};

class CGameMenuItem7EA1C : public CGameMenuItem
{
public:
    int at20; // text align
    CGameMenu *at24;
    int at28;
    void(*at2c)(CGameMenuItem7EA1C *);
    int at30;
    IniFile *at34;
    char at38[16];
    char at48[16];
    CGameMenuItem7EA1C();
    CGameMenuItem7EA1C(const char *a1, int a2, int a3, int a4, int a5, const char *a6, const char *a7, int a8, int a9, void(*a10)(CGameMenuItem7EA1C *), int a11);
    void Setup(void);
    virtual void Draw(void);
    virtual bool Event(CGameMenuEvent &);
};

class CGameMenuItem7EE34 : public CGameMenuItem
{
public:
    int at20;
    int at24;
    CGameMenu *at28;
    CGameMenu *at2c;
    CGameMenuItem7EE34();
    CGameMenuItem7EE34(const char *a1, int a2, int a3, int a4, int a5, int a6);
    void Setup(void);
    virtual void Draw(void);
    virtual bool Event(CGameMenuEvent &);
};

class CGameMenuItemChain7F2F0 : public CGameMenuItemChain
{
public:
    int at34;
    CGameMenuItemChain7F2F0();
    CGameMenuItemChain7F2F0(char *a1, int a2, int a3, int a4, int a5, int a6, CGameMenu *a7, int a8, void(*a9)(CGameMenuItemChain *), int a10);
    //virtual void Draw(void);
    virtual bool Event(CGameMenuEvent &);
};

class CGameMenuItemBitmap : public CGameMenuItem
{
public:
    int at20;
    CGameMenuItemBitmap();
    CGameMenuItemBitmap(const char *, int, int, int, int);
    virtual void Draw(void);
    virtual bool Event(CGameMenuEvent &);
};

class CGameMenuItemBitmapLS : public CGameMenuItemBitmap
{
public:
    int at24;
    int at28;
    CGameMenuItemBitmapLS();
    CGameMenuItemBitmapLS(const char *, int, int, int, int);
    virtual void Draw(void);
    virtual bool Event(CGameMenuEvent &);
};

class CGameMenuItemKeyList : public CGameMenuItem
{
public:
    void(*pCallback)(CGameMenuItemKeyList *);
    int at24;
    int nRows;
    int nTopDelta;
    int nFocus;
    int nGameFuncs;
    bool bScan;
    CGameMenuItemKeyList();
    CGameMenuItemKeyList(const char * a1, int a2, int a3, int a4, int a5, int a6, int a7, void(*a8)(CGameMenuItemKeyList *));
    void Scan(void);
    virtual void Draw(void);
    virtual bool Event(CGameMenuEvent &);
    virtual bool MouseEvent(CGameMenuEvent &);
};

class CGameMenuItemSlider : public CGameMenuItem
{
public:
    int *pValue;
    int nValue;
    int nRangeLow;
    int nRangeHigh;
    int nStep;
    void(*pCallback)(CGameMenuItemSlider *);
    int nSliderTile;
    int nCursorTile;
    CGameMenuItemSlider();
    CGameMenuItemSlider(const char *, int, int, int, int, int, int, int, int, void(*)(CGameMenuItemSlider *), int, int);
    CGameMenuItemSlider(const char *, int, int, int, int, int *, int, int, int, void(*)(CGameMenuItemSlider *), int, int);
    virtual void Draw(void);
    virtual bool Event(CGameMenuEvent &);
    virtual bool MouseEvent(CGameMenuEvent &);
};

class CGameMenuItemSliderFloat : public CGameMenuItem
{
public:
    float *pValue;
    float fValue;
    float fRangeLow;
    float fRangeHigh;
    float fStep;
    void(*pCallback)(CGameMenuItemSliderFloat *);
    int nSliderTile;
    int nCursorTile;
    CGameMenuItemSliderFloat();
    CGameMenuItemSliderFloat(const char *, int, int, int, int, float, float, float, float, void(*)(CGameMenuItemSliderFloat *), int, int);
    CGameMenuItemSliderFloat(const char *, int, int, int, int, float *, float, float, float, void(*)(CGameMenuItemSliderFloat *), int, int);
    virtual void Draw(void);
    virtual bool Event(CGameMenuEvent &);
};

class CGameMenuItemZEdit : public CGameMenuItem
{
public:
    char *at20;
    int at24;
    int at28;
    void(*at2c)(CGameMenuItemZEdit *, CGameMenuEvent *);
    char at30;
    char at31;
    char at32;
    CGameMenuItemZEdit();
    CGameMenuItemZEdit(const char *, int, int, int, int, char *, int, char, void(*)(CGameMenuItemZEdit *, CGameMenuEvent *), int);
    void AddChar(char);
    void BackChar(void);
    virtual void Draw(void);
    virtual bool Event(CGameMenuEvent &);
};

class CGameMenuItemZEditBitmap : public CGameMenuItem
{
public:
    char *at20;
    int at24;
    int at28;
    CGameMenuItemBitmapLS *at2c;
    void(*at30)(CGameMenuItemZEditBitmap *, CGameMenuEvent *);
    char at34;
    char at35;
    char at36;
    char at37;
    CGameMenuItemZEditBitmap();
    CGameMenuItemZEditBitmap(char *, int, int, int, int, char *, int, char, void(*)(CGameMenuItemZEditBitmap *, CGameMenuEvent *), int);
    void AddChar(char);
    void BackChar(void);
    virtual void Draw(void);
    virtual bool Event(CGameMenuEvent &);
};

class CGameMenuItemQAV : public CGameMenuItem
{
public:
    const char *at20;
    DICTNODE *at24;
    QAV *at28;
    int at2c;
    int at30;
    bool bWideScreen;
    bool bClearBackground;
    CGameMenuItemQAV();
    CGameMenuItemQAV(const char *, int, int, int, const char *, bool widescreen = false, bool clearbackground = false);
    virtual void Draw(void);
    virtual bool Event(CGameMenuEvent &);
    void Reset(void);
};

class CGameMenuItemZCycle : public CGameMenuItem
{
public:
    int m_nItems;
    int at24;
    int at28;
    int at2c;
    int at30;
    const char *at34[kMaxGameCycleItems];
    void(*atb4)(CGameMenuItemZCycle *);
    CGameMenuItemZCycle();
    CGameMenuItemZCycle(const char *, int, int, int, int, int, void(*)(CGameMenuItemZCycle *), const char **, int, int);
    ~CGameMenuItemZCycle();
    virtual void Draw(void);
    virtual bool Event(CGameMenuEvent &);
    void Add(const char *, bool);
    void Next(void);
    void Prev(void);
    void Clear(void);
    void SetTextArray(const char **, int, int);
    void SetTextIndex(int);
};

class CGameMenuItemYesNoQuit : public CGameMenuItem
{
public:
    int at20;
    int at24;
    int at28;
    CGameMenuItemYesNoQuit();
    CGameMenuItemYesNoQuit(const char *, int, int, int, int, int, int, int);
    virtual void Draw(void);
    virtual bool Event(CGameMenuEvent &);
};

class CGameMenuItemPicCycle : public CGameMenuItem
{
public:
    int m_nItems;
    int at24;
    int at28;
    int at2c;
    int at30[kMaxPicCycleItems];
    void(*atb0)(CGameMenuItemPicCycle *);
    int atb4;
    CGameMenuItemPicCycle();
    CGameMenuItemPicCycle(int, int, void(*)(CGameMenuItemPicCycle *), int *, int, int);
    virtual void Draw(void);
    virtual bool Event(CGameMenuEvent &);
    void Add(int, bool);
    void Next(void);
    void Prev(void);
    void Clear(void);
    void SetPicArray(int *, int, int);
    void SetPicIndex(int);
};

class CGameMenuItemPassword : public CGameMenuItem
{
public:
    char at20[9];
    char at29[9];
    int at32;
    char at36;
    int at37;
    char at3b[32];
    int at5b;
    CGameMenuItemZBool *at5f;
    CGameMenuItemPassword();
    CGameMenuItemPassword(const char *, int, int, int);
    virtual void Draw(void);
    virtual bool Event(CGameMenuEvent &);
};


class CGameMenu
{
public:
    int m_nItems;
    int m_nFocus;
    int at8;
    char atc;
    CGameMenuItem *pItemList[kMaxGameMenuItems]; // atd
    CGameMenu();
    CGameMenu(int);
    ~CGameMenu();
    void InitializeItems(CGameMenuEvent &event);
    void Draw(void);
    bool Event(CGameMenuEvent &event);
    void Add(CGameMenuItem *pItem, bool active);
    void SetFocusItem(int nItem);
    void SetFocusItem(CGameMenuItem *Item);
    bool CanSelectItem(int nItem);
    void FocusPrevItem(void);
    void FocusNextItem(void);
    bool IsFocusItem(CGameMenuItem *pItem);
    bool MouseEvent(CGameMenuEvent &event);
};

class CGameMenuMgr
{
public:
    static bool m_bInitialized;
    static bool m_bActive;
    CGameMenu *pActiveMenu;
    CGameMenu *pMenuStack[8];
    int nMenuPointer;
    int32_t m_mouselastactivity;
    int32_t m_mousewake_watchpoint, m_menuchange_watchpoint;
    int32_t m_mousecaught;
    vec2_t m_prevmousepos, m_mousepos, m_mousedownpos;
    CGameMenuMgr();
    ~CGameMenuMgr();
    void InitializeMenu(void);
    void DeInitializeMenu(void);
    bool Push(CGameMenu *pMenu, int data);
    void Pop(void);
    void Draw(void);
    void Clear(void);
    void Process(void);
    void Deactivate(void);
    bool MouseOutsideBounds(vec2_t const * const pos, const int32_t x, const int32_t y, const int32_t width, const int32_t height);
};

extern CMenuTextMgr gMenuTextMgr;
extern CGameMenuMgr gGameMenuMgr;

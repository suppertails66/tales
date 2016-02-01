;==============================================================
; WLA-DX banking setup
;==============================================================
.memorymap
defaultslot 0
slotsize $8000
slot 0 $0000
.endme

.rombankmap
bankstotal 1
banksize $8000
banks 1
.endro

;==============================================================
; SDSC tag and SMS rom header
;==============================================================
.sdsctag 1.10,"nullname","nulldesc","nullauthor"

;==============================================================================
; RAM variable defines
;==============================================================================
.define CurrentAreaID $D2AA

.define CurrentSeaFoxInventoryPos $D034
.define CurrentInventoryPos $D035
.define EquippedItem $D036

.define UnlockedItemsBitfieldByte0 $D030
.define UnlockedItemsBitfieldByte1 $D031
.define UnlockedItemsBitfieldByte2 $D032
.define UnlockedSeaFoxItemsBitfield $D033

.define ButtonsPressed $D13A		; RAM location of controller buttons
					; currently depressed
.define ButtonsTriggered $D14A		; RAM location of buttons depressed
					; on current frame
					
.define InventorySlots $D024		; RAM location of item slots
.define SeaFoxInventorySlots $D028	; RAM location of Sea Fox item slots

.define InventoryUpItem $D024		; RAM location of "up" hotkey item ID
.define InventoryRightItem $D025	; RAM location of "right" hotkey item ID
.define InventoryDownItem $D026		; RAM location of "down" hotkey item ID
.define InventoryLeftItem $D027		; RAM location of "left" hotkey item ID

.define SeaFoxUpItem $D028		; RAM location of "up" Sea Fox item ID
.define SeaFoxRightItem $D029		; RAM location of "right" Sea Fox item ID
.define SeaFoxDownItem $D02A		; RAM location of "down" Sea Fox item ID
.define SeaFoxLeftItem $D02B		; RAM location of "left" Sea Fox item ID

.define HUDTilemapBuffer $D044		; RAM location of the tilemap buffer used
					; to save priority settings for the tiles
					; beneath the HUD, used when pausing

.define ItemCollectionTilemapBuffer $D084 ; RAM location of the tilemap buffer used
					  ; to save priority settings for the tiles
					  ; used when collecting an item
					  
; RAM locations of the tilemap buffers for each of the pause screen hotswap items.
; It's OK to put these in the item collection tilemap buffer because
; it's impossible to pause during the item collection sequence.
.define UpItemTilemapBuffer ItemCollectionTilemapBuffer+0
.define DownItemTilemapBuffer ItemCollectionTilemapBuffer+12
.define LeftItemTilemapBuffer ItemCollectionTilemapBuffer+24
.define RightItemTilemapBuffer ItemCollectionTilemapBuffer+36

.define ItemTilemapBufferHeightWidth $0403	; height and width of each item
						; icon's tilemap buffer (first
						; byte is height, second is
						; width: size is 3x4)

.define UpItemTilemapLocationAddress $399E
.define RightItemTilemapLocationAddress $3AA8
.define DownItemTilemapLocationAddress $3BDE
.define LeftItemTilemapLocationAddress $3A94

.define SpriteRedrawFlag $D136		; If nonzero, indicates that the local
					; sprite table should be copied to VRAM

.define GraphicsLoadRequest $D3A4	; ID of a graphic to be loaded
.define GraphicsLoadWriteAddress $D3A9	; 16-bit VRAM write address of graphic
					; to be loaded

.define GraphicReloadFlags $D34E	; Bitfield polled by VBlank handler
					; to check if certain objects need to
					; have new graphics loaded.

.define GraphicReloadFlags2 $D351	; Bitfield polled by VBlank handler
					; to check if certain objects need to
					; have new graphics loaded.

.define LoadedObjectSlotsStart $D500	; Start of the loaded object slots
					; in RAM

.define TailsObjectSlot $D500		; Start of Tails object slot

.define RemoteRobotObjectSlot $D540	; Start of Remote Robot object slot
					
.define TailsGlobalFlags $D504		; Global object flags for Tails object

.define LocalSpriteYTable $DB00		; Start of local sprite y-position
					; table
.define LocalSpriteXPatternTable $DB40	; Start of local sprite x-position
					; and pattern number table
				
;.define ScreenXOffset $28		; X and y offsets to add to coordinates
					; to convert to an onscreen position
;.define ScreenYOffset $50
				
.define ScreenXOffset $30		; X and y offsets to add to coordinates
					; to convert to an onscreen position
.define ScreenYOffset $10
					
.define UpItemSpriteY ScreenYOffset+$20-1	; Y-coordinates of item sprites
.define RightItemSpriteY ScreenYOffset+$48-1
.define DownItemSpriteY ScreenYOffset+$70-1
.define LeftItemSpriteY ScreenYOffset+$48-1
					
.define UpItemSprite1X ScreenXOffset+$48	; X-coordinates of item sprites
.define UpItemSprite2X ScreenXOffset+$50
.define RightItemSprite1X ScreenXOffset+$70
.define RightItemSprite2X ScreenXOffset+$78
.define DownItemSprite1X ScreenXOffset+$48	
.define DownItemSprite2X ScreenXOffset+$50
.define LeftItemSprite1X ScreenXOffset+$20
.define LeftItemSprite2X ScreenXOffset+$28
					
.define UpItemSprite1Pattern $0		; Pattern indices of item sprites
.define UpItemSprite2Pattern $2
.define DownItemSprite1Pattern $4
.define DownItemSprite2Pattern $6
.define LeftItemSprite1Pattern $8
.define LeftItemSprite2Pattern $A
.define RightItemSprite1Pattern $C
.define RightItemSprite2Pattern $E

.define UpItemYAddress1 $DB00		; Y-coordinate entries of items
.define UpItemYAddress2 $DB01
.define DownItemYAddress1 $DB02
.define DownItemYAddress2 $DB03
.define LeftItemYAddress1 $DB04
.define LeftItemYAddress2 $DB05
.define RightItemYAddress1 $DB06
.define RightItemYAddress2 $DB07

.define UpItemXAddress1 $DB40		; X-coordinate entries of items
.define UpItemXAddress2 $DB42
.define DownItemXAddress1 $DB44
.define DownItemXAddress2 $DB46
.define LeftItemXAddress1 $DB48
.define LeftItemXAddress2 $DB4A
.define RightItemXAddress1 $DB4C
.define RightItemXAddress2 $DB4E

.define UpItemPatternAddress1 $DB41	; Pattern entries of items
.define UpItemPatternAddress2 $DB43
.define DownItemPatternAddress1 $DB45
.define DownItemPatternAddress2 $DB47
.define LeftItemPatternAddress1 $DB49
.define LeftItemPatternAddress2 $DB4B
.define RightItemPatternAddress1 $DB4D
.define RightItemPatternAddress2 $DB4F

.define SoundEffectTrigger $DE04	; Interrupt handler polls this value
					; to detect if sound effect should
					; be played

;==============================================================================
; Constant defines
;==============================================================================
.define inventoryLowerLimit $6		; min inventory value
.define inventoryUpperLimit $18		; max inventory value + 1

.define seaFoxInventoryLowerLimit $0	; min inventory value
.define seaFoxInventoryUpperLimit $8	; max inventory value + 1

.define upButtonBit 0
.define downButtonBit 1
.define leftButtonBit 2
.define rightButtonBit 3
.define oneButtonBit 4
.define twoButtonBit 5
.define startButtonBit 7

.define upButtonMask $01
.define downButtonMask $02
.define leftButtonMask $04
.define rightButtonMask $08
.define oneButtonMask $10
.define twoButtonMask $20
.define startButtonMask $80

.define InventoryUpItemOffset $0	; Offset of "up" hotkey item ID from start
.define InventoryRightItemOffset $3	; Offset of "right" hotkey item ID from start
.define InventoryDownItemOffset $1	; Offset of "down" hotkey item ID from start
.define InventoryLeftItemOffset $2	; Offset of "left" hotkey item ID from start

.define InventoryItemsVRAMAddress $0	; Address of inventory item icons in VRAM
.define InventoryItemVRAMSpace $80	; Size of a loaded inventory item in VRAM

.define InventoryUpVRAMAddress $0	; VRAM address of inventory up item graphics
.define InventoryDownVRAMAddress $80	; VRAM address of inventory down item graphics
.define InventoryLeftVRAMAddress $100	; VRAM address of inventory left item graphics
.define InventoryRightVRAMAddress $180	; VRAM address of inventory right item graphics

.define NumInventorySlots 4		; Number of inventory equip slots

.define SpriteMappingsBank $F		; Bank containing the sprite mappings

.define ObjectGlobalFlagsOffset $4	; Offset in loaded object slot of
					; the global bit flags.
.define ObjectInvisibilityBitFlag 7	; Bit # in global flags byte of
					; object invisibility flag. Object is
					; not drawn (sprites are not written
					; to local sprite table) if set.

.define TailsGraphicReloadBit 7		; Bit # of GraphicReloadFlags
					; indicating Tails' graphics need to be
					; reloaded

.define RemoteRobotGraphicReloadBit 7	; Bit # of GraphicReloadFlags2
					; indicating Tails' graphics need to be
					; reloaded

.define ItemIDGraphicLoadOffset $10	; Offset to be added to an item ID to
					; get the index of its corresponding
					; graphic, used in calls to
					; LoadRequestedGraphic
					
.define NumLoadedObjectSlots $18	; Number of loaded objects slots

.define LoadedObjectSlotSize $40	; Size of a loaded object slot

.define NumLocalSpriteTableEntries $40		; Number of entries in sprite
						; y-position table

.define NumLocalSpriteTableTempEntries $37	; Number of non-permanent
						; sprites in local table.
						; Non-permanent sprites are
						; basically everything except
						; the HUD, which resides at
						; the end of the table
						
.define SpriteDisabledYPosition $E0	; Indicates disabled sprite in sprite
					; y-position table
					
.define SpriteRedrawFlagConst $FF	; Value indicating sprites should be
					; redrawn. Any nonzero value will do.
					
;.define EquipItemSound $CE
.define EquipItemSound $A9		; Sound effect to play when an item
					; is equipped
.define FailureItemSound $B0		; Sound effect to play when an item
					; can't be equipped
.define SetItemSound $C7		; Sound effect to play when an item
					; is set to a slot

;==============================================================================
; Routine defines
;==============================================================================
.define WaitForInterrupt $065B		; Returns after VBlank is handled
.define InventoryUpdate $154A		; Checks if player pressed button to
					; update inventory and updates
					; equipped item ID if so
.define LoadNewInventoryItem $1579	; Triggers inventory item change
					; sequence to whatever item ID
					; is in memory
.define ChangeSlot2 $1B8E		; Sets slot 2 bank to A
.define RedrawObjects $2181		; Writes all object graphic sprites to
					; local table
.define GenerateAndLoadRequestedGraphic $76EC	
					; If GraphicsLoadRequest is nonzero,
					; loads parameters and graphic for
					; the requested ID
.define LoadParametersAndGraphic $76EC	; If GraphicsLoadRequest is nonzero,
					; writes graphic for the requested ID
					; to VRAM using parameters in RAM
.define LoadRequestedGraphic $76F8	; If GraphicsLoadRequest is nonzero,
					; writes graphic for the requested ID
					; to VRAM using parameters in RAM
.define GenerateGraphicParameters $7778	; Writes to RAM parameters for a
					; graphic to be loaded

.define TilemapSaveBank $E
.define TilemapSaveBankedAddress $9FB8	; Saves part of tilemap to a buffer

.define TilemapRestoreBank $E
.define TilemapRestoreBankedAddress $9FE5	; Restore part of tilemap
						; from a buffer
					
.define CodeActualStart $7D0A

.macro BRANCHIFONSEAFOXMAP
  ld a,(CurrentAreaID)			; check if we're using Sea Fox
  cp $06
  jr z,\1
  cp $07
  jr z,\1
  cp $0B
  jr z,\1
.endm

.bank 0 slot 0
.org $0000

.section "InventoryHotswap" force

;==============================================================================
; Start of code in temporary ROM
;==============================================================================
;CodeStart:
;  jp NewPauseStart	; jump to real code for testing

;==============================================================================
; In real hack, this will be used to trigger our code
;==============================================================================
;12DB:
;  call $6C4	; call new pause handler instead of main pause loop

;12DB:
;  call $7D0A	; actually, use this instead
 
;==============================================================================
; Starts up our new pause loop. To be placed at $7D0A, the filler space
; in bank 1.
;==============================================================================
NewPauseStart:
  ; Disable all sprites (set y-position to E0)
  ld hl,LocalSpriteYTable
  ld b,NumLocalSpriteTableTempEntries
    -:
    ld a,SpriteDisabledYPosition	; mark all sprites as disabled
    ld (hl),a
    inc hl
    djnz -
  
  
  ; Redraw sprites (copy local table to VRAM so existing sprites are not visible)
  ld a,SpriteRedrawFlagConst
  ld (SpriteRedrawFlag),a		; mark that sprites should be redrawn
  call WaitForInterrupt			; wait for VBlank
  
  ; Load inventory graphics
  
  ; Get starting address of items to draw
  call CodeActualStart+TestForSeaFoxMap
  or a
  jr nz,+			; branch if using Sea Fox items
    ld de,InventorySlots
    jr NewPauseStartLoadGraphics
  +:
    ld de,SeaFoxInventorySlots
    
  ; Load the four inventory graphics we need.
  ; We sacrifice Tails' graphics for this purpose.
  NewPauseStartLoadGraphics:
  ld hl,InventoryItemsVRAMAddress
  ld b,NumInventorySlots
  -:
    ; Get next item ID and load graphic
    ld a,(de)
    inc de
    add a,ItemIDGraphicLoadOffset	; convert from item to graphic index
    ld (GraphicsLoadRequest),a
    push de
    push hl
    call GenerateGraphicParameters	; generate loading parameters
					; this trashes HL and DE
    pop hl
    ld (GraphicsLoadWriteAddress),hl	; overwrite original write address
    push hl
    push bc
    call LoadRequestedGraphic		; load the graphic to the address
					; this trashes BC, HL, and DE(?)
    pop bc
    pop hl
    pop de
    
    ; Advance HL to next write position
    push de				; save item getpos
    ld de,InventoryItemVRAMSpace
    add hl,de				; add size of slot to putpos
    pop de				; restore item getpos
    
    ; Loop over all slots
    djnz -
    
  ; Save parts of the tilemap that we need to alter to a temporary buffer
  
  ld a,TilemapSaveBank
  call ChangeSlot2	; change to bank containing tilemap save code
  
  ; Save up item tilemap
  ld hl,UpItemTilemapLocationAddress
  ld bc,ItemTilemapBufferHeightWidth
  ld iy,UpItemTilemapBuffer
  call TilemapSaveBankedAddress
  
  ; Save right item tilemap
  ld hl,RightItemTilemapLocationAddress
  ld bc,ItemTilemapBufferHeightWidth
  ld iy,RightItemTilemapBuffer
  call TilemapSaveBankedAddress
  
  ; Save down item tilemap
  ld hl,DownItemTilemapLocationAddress
  ld bc,ItemTilemapBufferHeightWidth
  ld iy,DownItemTilemapBuffer
  call TilemapSaveBankedAddress
  
  ; Save left item tilemap
  ld hl,LeftItemTilemapLocationAddress
  ld bc,ItemTilemapBufferHeightWidth
  ld iy,LeftItemTilemapBuffer
  call TilemapSaveBankedAddress
  
  ; Draw inventory graphic sprites
  
  ; Up item y
  ld a,UpItemSpriteY
  ld hl,UpItemYAddress1
  ld (hl),a
;  ld hl,UpItemYAddress2
  inc hl
  ld (hl),a
  
  ; Down item y
  ld a,DownItemSpriteY
  ld hl,DownItemYAddress1
  ld (hl),a
;  ld hl,DownItemYAddress2
  inc hl
  ld (hl),a
  
  ; Left item y
  ld a,LeftItemSpriteY
  ld hl,LeftItemYAddress1
  ld (hl),a
;  ld hl,LeftItemYAddress2
  inc hl
  ld (hl),a
  
  ; Right item y
  ld a,RightItemSpriteY
  ld hl,RightItemYAddress1
  ld (hl),a
;  ld hl,RightItemYAddress2
  inc hl
  ld (hl),a
  
  ; Up item x
  ld a,UpItemSprite1X
  ld hl,UpItemXAddress1
  ld (hl),a
  ld a,UpItemSprite2X
  ld hl,UpItemXAddress2
  ld (hl),a
  
  ; Down item x
  ld a,DownItemSprite1X
  ld hl,DownItemXAddress1
  ld (hl),a
  ld a,DownItemSprite2X
  ld hl,DownItemXAddress2
  ld (hl),a
  
  ; Left item x
  ld a,LeftItemSprite1X
  ld hl,LeftItemXAddress1
  ld (hl),a
  ld a,LeftItemSprite2X
  ld hl,LeftItemXAddress2
  ld (hl),a
  
  ; Right item x
  ld a,RightItemSprite1X
  ld hl,RightItemXAddress1
  ld (hl),a
  ld a,RightItemSprite2X
  ld hl,RightItemXAddress2
  ld (hl),a
  
  ; Up item pattern
  ld a,UpItemSprite1Pattern
  ld hl,UpItemPatternAddress1
  ld (hl),a
  ld a,UpItemSprite2Pattern
  ld hl,UpItemPatternAddress2
  ld (hl),a
  
  ; Down item pattern
  ld a,DownItemSprite1Pattern
  ld hl,DownItemPatternAddress1
  ld (hl),a
  ld a,DownItemSprite2Pattern
  ld hl,DownItemPatternAddress2
  ld (hl),a
  
  ; Left item pattern
  ld a,LeftItemSprite1Pattern
  ld hl,LeftItemPatternAddress1
  ld (hl),a
  ld a,LeftItemSprite2Pattern
  ld hl,LeftItemPatternAddress2
  ld (hl),a
  
  ; Right item pattern
  ld a,RightItemSprite1Pattern
  ld hl,RightItemPatternAddress1
  ld (hl),a
  ld a,RightItemSprite2Pattern
  ld hl,RightItemPatternAddress2
  ld (hl),a
  
  ; Redraw sprites
  ld a,SpriteRedrawFlagConst
  ld (SpriteRedrawFlag),a		; mark that sprites need to be reloaded
  ; Drop into pause loop below, which starts with a
  ; call to WaitForInterrupt that will load the new sprites
  

;==============================================================================
; Replacement for original pause loop
;==============================================================================
NewPauseLoop:
  ; Wait frame
  call WaitForInterrupt			; wait for screen redraw
  call GenerateAndLoadRequestedGraphic	; load any pending graphics
  
  ; Check if player triggered an unpause
  ld a,(ButtonsTriggered)	; get buttons triggered this frame
  and startButtonMask
  jr nz,NewPauseEnd		; exit pause loop if Start triggered
  
  ; Check if the player is holding down the Start button.
  ; If so, and a direction button is triggered, run the item switch
  ; routine and then unpause for a "quick-swap".
  ld a,(ButtonsPressed)	; get buttons pressed this frame
  and startButtonMask
  jr z,NewPauseCheckForButtonHotswap	; branch if not holding start
    ld a,(ButtonsTriggered)	; get buttons triggered this frame
    and upButtonMask|downButtonMask|leftButtonMask|rightButtonMask
    jr z,NewPauseCheckForButtonHotswap	; branch if no direction pressed
      ; Equip item
      call CodeActualStart+HotswapEquipItem
      call WaitForInterrupt			; wait for screen redraw
      call GenerateAndLoadRequestedGraphic	; load any pending graphics
      jr NewPauseEnd				; unpause
  
  NewPauseCheckForButtonHotswap:
  
  ; Check if player is holding a hotswap button
  ld a,(ButtonsPressed)
  and oneButtonMask|twoButtonMask
  jr z,InventoryUpdateStart	; branch if neither button pressed
  
  ; Hotswap button pressed: do hotswap update
  bit oneButtonBit,a
  jr z,+
    call CodeActualStart+HotswapEquipItem	; I button: do item equip update
    jr NewPauseLoop	; Go to start of loop (skip inventory update)
  +: 
    bit twoButtonBit,a
    jr z,NewPauseLoop
    call CodeActualStart+HotswapSetItem		; II button: do item set update
    jr NewPauseLoop	; Go to start of loop (skip inventory update)
  
  ; Do player inventory equipment update
  InventoryUpdateStart:
  call InventoryUpdate
  
  ; If player pressed button to change equipped item,
  ; player inventory change animation
  ld a,(ButtonsTriggered)
  and leftButtonMask|rightButtonMask	; check if left or right triggered
  call nz,LoadNewInventoryItem
  
  jr NewPauseLoop
  
;==============================================================================
; Exit from pause
;==============================================================================
NewPauseEnd:
  ; Remove inventory graphic sprites
  call CodeActualStart+DisableLocalSprites
  ld a,SpriteRedrawFlagConst
  ld (SpriteRedrawFlag),a		; mark that sprites need to be reloaded
    
  ; Restore the tilemap from the temporary buffer
  ld a,TilemapRestoreBank
  call ChangeSlot2	; change to bank containing tilemap restore code
  
  ; Restore up item tilemap
  ld hl,UpItemTilemapLocationAddress
  ld bc,ItemTilemapBufferHeightWidth
  ld iy,UpItemTilemapBuffer
  call TilemapRestoreBankedAddress
  
  ; Restore right item tilemap
  ld hl,RightItemTilemapLocationAddress
  ld bc,ItemTilemapBufferHeightWidth
  ld iy,RightItemTilemapBuffer
  call TilemapRestoreBankedAddress
  
  ; Restore down item tilemap
  ld hl,DownItemTilemapLocationAddress
  ld bc,ItemTilemapBufferHeightWidth
  ld iy,DownItemTilemapBuffer
  call TilemapRestoreBankedAddress
  
  ; Restore left item tilemap
  ld hl,LeftItemTilemapLocationAddress
  ld bc,ItemTilemapBufferHeightWidth
  ld iy,LeftItemTilemapBuffer
  call TilemapRestoreBankedAddress

  ; Reload Tails graphics
  ld hl,GraphicReloadFlags
  set TailsGraphicReloadBit,(hl)  ; set bit indicating Tails graphics need
				  ; reload
				  
  ; Reload Remote Robot graphics if needed
  ld a,(RemoteRobotObjectSlot)		; check for presence of Remote Robot
  or a
  jr z,+				; branch if Remote Robot not active
    ld hl,GraphicReloadFlags2
    set RemoteRobotGraphicReloadBit,(hl)	; mark for reload
  +:
  call WaitForInterrupt		; wait for interrupt handler to reload
				; Tails graphics
				
  ret
  
;==============================================================================
; Handle hotswap item equip functionality
;==============================================================================
HotswapEquipItem:
  ; Determine which direction, if any, the user triggered
  call CodeActualStart+TestForSeaFoxMap
  ld c,a		; save sea fox use value to C
  
  or A
  jr nz,+			; branch if using Sea Fox items
    ld hl,InventorySlots
    jr HotswapEquipButtonCheck
  +:
    ld hl,SeaFoxInventorySlots
    
  HotswapEquipButtonCheck:
    ; Check for regular items
    ld a,(ButtonsTriggered)
    bit upButtonBit,a
    jr z,+
      ld a,InventoryUpItemOffset
      jr HotswapEquipWriteItem ; up triggered
    +:
    bit rightButtonBit,a
    jr z,+	; right triggered
      ld a,InventoryRightItemOffset
      jr HotswapEquipWriteItem ; right triggered
    +:
    bit downButtonBit,a
    jr z,+	; down triggered
      ld a,InventoryDownItemOffset
      jr HotswapEquipWriteItem ; down triggered
    +:
    bit leftButtonBit,a
    jr z,+
      ld a,InventoryLeftItemOffset
      jr HotswapEquipWriteItem ; left triggered
    +:
      ret			; no direction triggered: do nothing
    
  HotswapEquipWriteItem:
  
  ; Put the address of the targeted item in HL
  ld e,a
  ld d,0
  add hl,de
    
  ; Equip the chosen item
  +:
  ld a,(hl)
  or a
  jr nz,+
    ld a,FailureItemSound
    ld (SoundEffectTrigger),a	; play failure sound
    ret		; don't equip if selected slot is null
  
  +:
  ld (EquippedItem),a	; equip item
  
  ; Set the bit position for this item ID
  ld hl,CodeActualStart+ObjectIDToBitTable
  ld e,a
  ld d,0
  add hl,de
  
  ld a,c	; get stored Sea Fox use value
  or a
  jr nz,+	; branch if using Sea Fox items
    ld a,(hl)
    ld (CurrentInventoryPos),a		; write new regular item position
    jr HotswapEquipUpdateSprites	; branch over Sea Fox code
  +:
    ld a,(hl)
    ld (CurrentSeaFoxInventoryPos),a	; write new Sea Fox position
    
  HotswapEquipUpdateSprites:
  
  ; Update displayed inventory icon
  ld a,(EquippedItem)
  add a,ItemIDGraphicLoadOffset
  ld (GraphicsLoadRequest),a
  call LoadParametersAndGraphic	; write new tiles for item
  
  ; Play equip sound effect
  ld a,EquipItemSound
  ld (SoundEffectTrigger),a
  
  ret
  
;==============================================================================
; Handle hotswap item set functionality
;==============================================================================
HotswapSetItem:
  ; Determine which direction, if any, the user triggered
  call CodeActualStart+TestForSeaFoxMap
  
  or A
  jr nz,+			; branch if using Sea Fox items
    ld hl,InventorySlots
    jr HotswapSetButtonCheck
  +:
    ld hl,SeaFoxInventorySlots
    
  HotswapSetButtonCheck:
    ; Check for regular items
    ld a,(ButtonsTriggered)
    bit upButtonBit,a
    jr z,+
      ld a,InventoryUpItemOffset
      ld de,InventoryUpVRAMAddress
      jr HotswapSetWriteItem ; up triggered
    +:
    bit rightButtonBit,a
    jr z,+	; right triggered
      ld a,InventoryRightItemOffset
      ld de,InventoryRightVRAMAddress
      jr HotswapSetWriteItem ; right triggered
    +:
    bit downButtonBit,a
    jr z,+	; down triggered
      ld a,InventoryDownItemOffset
      ld de,InventoryDownVRAMAddress
      jr HotswapSetWriteItem ; down triggered
    +:
    bit leftButtonBit,a
    jr z,+
      ld a,InventoryLeftItemOffset
      ld de,InventoryLeftVRAMAddress
      jr HotswapSetWriteItem ; left triggered
    +:
      ret			; no direction triggered: do nothing
      
  HotswapSetWriteItem:
  
  push de	; save object graphic VRAM write location
  
  ; Remember starting address for duplicate item check
  push hl
  pop de
  
  ; Get the address of the targeted slot
  ld c,a
  ld b,0
  add hl,bc
  
  ; Check if item already in a slot
  ld a,(EquippedItem)
  ld c,a		; get equipped item ID
  ld b,NumInventorySlots
  -:
    ld a,(de)
    cp c		; compare this slot with currently equipped item
    jr nz,+		; branch if items are different
      ; If item IDs match, swap items by placing the item currently occupying
      ; the target slot in the slot containing the item that matches the one
      ; we're trying to place in the target slot. The rest of the routine will
      ; take care of putting the target item in the target slot.
      ld a,(hl)		; get item in the slot the player wants to set
      ld (de),a		; place in slot containing would-be duplicate
      
      ; Write graphic to VRAM
      add a,ItemIDGraphicLoadOffset	; convert item ID to graphic load ID
      ld (GraphicsLoadRequest),a	; write
      
      ld a,b
      dec a
      add a,a
      ld e,a	; de = lookup table position
      ld d,0
      
      push hl	; save target slot address
      
      ld hl,CodeActualStart+ItemSpriteVRAMLookupTable
      add hl,de
      ld a,(hl)
      ld e,a
      inc hl
      ld a,(hl)
      ld d,a		; de = VRAM write address
  
      push de
      call GenerateGraphicParameters
      pop de
      ld (GraphicsLoadWriteAddress),de	; set write address
      call LoadRequestedGraphic		; load graphic to address
      
      pop hl	; restore target slot address
      
     jr HotswapSetWriteSlot	; branch: there should be at most one duplicate
    +:
    inc de
    djnz -	; loop over all slots
    
  HotswapSetWriteSlot:
    
  ; Place the item in the chosen slot
  ld a,(EquippedItem)
  ld (hl),a
  
  ; Update sprite graphic
  add a,ItemIDGraphicLoadOffset		; convert item ID to graphic load ID
  ld (GraphicsLoadRequest),a
  call GenerateGraphicParameters
  pop hl	; get address of graphic
  ld (GraphicsLoadWriteAddress),hl	; set write address
  call LoadRequestedGraphic		; load graphic to address
  
  ; Play selection sound
  ld a,SetItemSound
  ld (SoundEffectTrigger),a
  
  ret
  
;==============================================================================
; Lookup table of item VRAM write addresses
;==============================================================================
ItemSpriteVRAMLookupTable
.dw InventoryRightVRAMAddress,InventoryLeftVRAMAddress
.dw InventoryDownVRAMAddress,InventoryUpVRAMAddress
  
;==============================================================================
; Disable all sprites in local table
;==============================================================================
DisableLocalSprites:
  ; Disable all sprites (set y-position to E0)
  ld hl,LocalSpriteYTable
  ld b,NumLocalSpriteTableTempEntries
    -:
    ld a,SpriteDisabledYPosition	; mark all sprites as disabled
    ld (hl),a
    inc hl
    djnz -

;==============================================================================
; Return nonzero value in A if on a Sea Fox map
;==============================================================================
TestForSeaFoxMap:
  ld a,(CurrentAreaID)			; check if we're using Sea Fox
  cp $06	; lake rocky
  jr z,+
  cp $07	; lake crystal
  jr z,+
  cp $0B	; battle fortress 1
  jr z,+
  
  ld a,$00;	; not on sea fox map: return zero in A
  ret;
  
  +:
  ld a,$FF;	; return nonzero value in A if on Sea Fox map
  ret;

;==============================================================================
; Table of item ID -> inventory slot equivalences
;==============================================================================
ObjectIDToBitTable
.db $00,$17,$16,$15,$14,$13,$12,$11, $07,$06,$0F,$0E,$0D,$0C,$0B,$0A
.db $09,$08,$07,$06,$05,$04,$03,$02, $01,$00,$10

.ends

PROGNAME =PAlib
OFILES   +=
ADD_LIBS +=
ARM7BIN         := -7 $(PAPATH)/lib/arm7/arm7.bin
PATH 			:= $(DEVKITARM)/bin:$(PATH)
TEXT1 			:= Japanese Training (using uLib and PALIB)
TEXT2 			:= Dev:cuicui666 Gfx:olimin & altarfinch
TEXT3 			:= http://sourceforge.net/projects/jptraining
ICON 			:= -b $(CURDIR)/../rsc/graphics/logo.bmp
LOGO			:= -o $(CURDIR)/../rsc/graphics/logo_wifi.bmp
INTERNAL_NAME	:= JPTRAINING
GAME_CODE		:= 000P
MAKER_CODE		:= 00
MAKER			:= -g $(GAME_CODE) $(MAKER_CODE) $(INTERNAL_NAME)

#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------
ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM)
endif
#---------------------------------------------------------------------------------
# TARGET is the name of the output, if this ends with _mb generates a multiboot image
# BUILD is the directory where object files & intermediate files will be placed
# SOURCES is a list of directories containing source code
# INCLUDES is a list of directories containing extra header files
#---------------------------------------------------------------------------------
TARGET		:=	$(shell basename $(CURDIR))
BUILD		:=	build
RELEASE_DIR	:=	release
VERSION		:=	0.8
JLPT4_DIR	:=	$(RELEASE_DIR)/JLPT4
FILES_DIR	:=	$(CURDIR)/rsc/files
SOURCES		:=	source source/jpt source/jpt/menus source/jpt/games source/jpt/files source/jpt/grids source/jpt/fonts source/jpt/data source/jpt/geometry source/jpt/scores source/jpt/components gfx data
INCLUDES	:=	include build data
EXPORT_DIR	:=	/c/ndsexamples/
ARCH		:=	-mthumb-interwork

# note: arm9tdmi isn't the correct CPU arch, but anything newer and LD
# *insists* it has a FPU or VFP, and it won't take no for an answer!
CFLAGS	:=	-g -Wall -O2 \
 		-mcpu=arm9tdmi -mtune=arm9tdmi -fomit-frame-pointer\
		-ffast-math \
		$(ARCH)

CFLAGS	+=	$(INCLUDE) -DARM9 -I$(DEVKITPRO)/PAlib/include/nds
CFLAGS	+=	$(INCLUDE) -DARM9 -I$(DEVKITPRO)/freetype/include

ASFLAGS	:=	-g $(ARCH)
LDFLAGS	:=	-g $(ARCH) -mno-fpu -L$(DEVKITPRO)/PAlib/lib -lpa9 -L$(DEVKITPRO)/freetype/lib -lfreetype

#---------------------------------------------------------------------------------
# the prefix on the compiler executables
#---------------------------------------------------------------------------------
PREFIX			:=	arm-eabi-

#---------------------------------------------------------------------------------
# any extra libraries we wish to link with the project
#---------------------------------------------------------------------------------
LIBS	:= -lul -lpa9 -lpng -lz -lfat -lnds9 -lfreetype
 
#---------------------------------------------------------------------------------
# list of directories containing libraries, this must be the top level containing
# include and lib
#---------------------------------------------------------------------------------
LIBDIRS	:=	$(DEVKITPRO)/libnds
  
#---------------------------------------------------------------------------------
# no real need to edit anything past this point unless you need to add additional
# rules for different file extensions
#---------------------------------------------------------------------------------
ifneq ($(BUILD),$(notdir $(CURDIR)))
#---------------------------------------------------------------------------------
 
export OUTPUT	:=	$(CURDIR)/$(TARGET)
export VPATH	:=	$(foreach dir,$(SOURCES),$(CURDIR)/$(dir))
export CC		:=	$(PREFIX)gcc
export CXX		:=	$(PREFIX)g++
export AR		:=	$(PREFIX)ar
export OBJCOPY	:=	$(PREFIX)objcopy

#---------------------------------------------------------------------------------
# use CXX for linking C++ projects, CC for standard C
#---------------------------------------------------------------------------------
export LD		:=	$(CXX)
 
CFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
SFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))
PCXFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.pcx)))
BINFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.bin)))
PNGFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.png)))
PALFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.pal)))
RAWFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.raw)))
MAPFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.map)))
JPEGFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.jpg)))
MODFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.mod)))
GIFFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.gif)))
TXTFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.txt)))
BMPFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.bmp)))
MP3FILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.mp3)))
 
export OFILES	:=	$(MP3FILES:.mp3=.o) $(MAPFILES:.map=.o) $(RAWFILES:.raw=.o) $(PALFILES:.pal=.o) $(BINFILES:.bin=.o) $(PNGFILES:.png=.o) $(PCXFILES:.pcx=.o) $(JPEGFILES:.jpg=.o) $(MODFILES:.mod=.o) $(GIFFILES:.gif=.o) $(TXTFILES:.txt=.o) $(BMPFILES:.bmp=.o)\
					$(CPPFILES:.cpp=.o) $(CFILES:.c=.o) $(SFILES:.s=.o)
 
export INCLUDE	:=	$(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir)) \
					$(foreach dir,$(LIBDIRS),-I$(dir)/include) \
					$(foreach dir,$(LIBDIRS),-I$(dir)/include/nds) \
					-I$(PAPATH)/include/nds\
					-I$(CURDIR)/$(BUILD)
 
export LIBPATHS	:=	$(foreach dir,$(LIBDIRS),-L$(dir)/lib)
 
.PHONY: $(BUILD) clean release upload
 
#---------------------------------------------------------------------------------
$(BUILD):
	@[ -d $@ ] || mkdir -p $@
	@make --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile
 
#---------------------------------------------------------------------------------
# TARGETS PERSOS
#---------------------------------------------------------------------------------
clean:
	@echo [INFO] --------------------------------
	@echo [INFO] Cleaning directory $(BUILD) for project $(TARGET)...
	@rm -fr $(BUILD)/* *.elf *.*ds* *.sav
	@echo [INFO] Cleaning done.

release:
	@echo [INFO] --------------------------------
	@echo [INFO] Release for project $(TARGET)...
	@echo [INFO] Cleaning 'release' directory...
	@rm -fr $(JLPT4_DIR)
	@mkdir $(JLPT4_DIR)
	@echo [INFO] Directory 'release' is clean.
	@echo [INFO] Copying files...
	@echo [INFO] Copying file '$(TARGET).nds'
	@cp $(CURDIR)/$(TARGET).nds $(JLPT4_DIR)
	
	@echo [INFO] Copying file '$(TARGET).sc.nds'
	@cp $(CURDIR)/$(TARGET).sc.nds $(JLPT4_DIR)
	
	@echo [INFO] Copying file '$(TARGET).ds.gba'
	@cp $(CURDIR)/$(TARGET).ds.gba $(JLPT4_DIR)
	
	@echo [INFO] Copying files from directory 'EN'
	@mkdir $(JLPT4_DIR)/EN
	@cp $(FILES_DIR)/EN/* $(JLPT4_DIR)/EN

	@echo [INFO] Copying files from directory 'FR'
	@mkdir $(JLPT4_DIR)/FR
	@cp $(FILES_DIR)/FR/* $(JLPT4_DIR)/FR
	
	@echo [INFO] Copying file 'DRAWINGS.DB'
	@cp $(FILES_DIR)/DRAWINGS.DB $(JLPT4_DIR)
	
	@echo [INFO] Copying file 'README.txt'
	@cp '$(CURDIR)/README.txt' $(JLPT4_DIR)

	@echo [INFO] Copying files from directory 'translationPack'
	@mkdir $(JLPT4_DIR)/translationPack
	@cp -r $(FILES_DIR)/translationPack/* $(JLPT4_DIR)/translationPack
	@rm -r $(JLPT4_DIR)/translationPack/csv/.svn
	@rm -r $(JLPT4_DIR)/translationPack/csv/EN/.svn
	@rm -r $(JLPT4_DIR)/translationPack/csv/FR/.svn
	
	@echo [INFO] Files copied.
	
	@echo [INFO] Zipping directory $(JLPT4_DIR)
	@tar -C $(RELEASE_DIR) -cjf $(RELEASE_DIR)/jptraining_v$(VERSION).tar.bz2 JLPT4
	
	@echo [INFO] Release done.

upload:
	@echo [INFO] --------------------------------
	@echo [INFO] Upload release to FTP...
	@ftp -s:upload.txt upload.sourceforge.net
	@echo [INFO] Upload done.

#---------------------------------------------------------------------------------
else
 
DEPENDS	:=	$(OFILES:.o=.d)
 
#---------------------------------------------------------------------------------
# main targets
#---------------------------------------------------------------------------------
$(OUTPUT).ds.gba	: 	$(OUTPUT).nds

$(OUTPUT).nds	: 	$(OUTPUT).bin

$(OUTPUT).bin	:	$(OUTPUT).elf
 
$(OUTPUT).elf	:	$(OFILES)
 
#---------------------------------------------------------------------------------
%.ds.gba: %.nds
	@echo built ... $(notdir $@)
	@dsbuild $< 
	@cp $(CURDIR)/../$(notdir $@) ../$(notdir $(OUTPUT)).sc.nds 

#---------------------------------------------------------------------------------
%.nds: %.bin
	
	@ndstool -c $@ -9 $(TARGET).bin $(ARM7BIN) $(MAKER) $(LOGO) $(ICON) "$(TEXT1);$(TEXT2);$(TEXT3)"

#---------------------------------------------------------------------------------
%.bin: %.elf
	
	@$(OBJCOPY) -O binary $(TARGET).elf $(TARGET).bin
 
#---------------------------------------------------------------------------------
%.elf:
	@echo $(LD)  $(LDFLAGS) -specs=ds_arm9.specs $(OFILES) $(LIBPATHS) $(LIBS) -o $(TARGET).elf
	@$(LD)  $(LDFLAGS) -specs=ds_arm9.specs $(OFILES) $(LIBPATHS) $(LIBS) -o $(TARGET).elf
 
#---------------------------------------------------------------------------------
# Compile Targets for C/C++
#---------------------------------------------------------------------------------
 
#---------------------------------------------------------------------------------
%.o : %.cpp
	@echo $(notdir $<)
	@$(CXX) -MM $(CFLAGS) -o $*.d $<
	@$(CXX) $(CFLAGS) -c $< -o$@
 
#---------------------------------------------------------------------------------
%.o : %.c
	@echo $(notdir $<)
	@$(CC) -MM $(CFLAGS) -o $*.d $<
	@$(CC)  $(CFLAGS) -c $< -o$@
 
#---------------------------------------------------------------------------------
%.o : %.s
	@echo $(notdir $<)
	@$(CC) -MM $(CFLAGS) -o $*.d $<
	@$(CC)  $(ASFLAGS) -c $< -o$@
 
define bin2o
	cp $(<) $(*).tmp
	$(OBJCOPY) -I binary -O elf32-littlearm -B arm \
	--rename-section .data=.rodata \
	--redefine-sym _binary_$*_tmp_start=$*\
	--redefine-sym _binary_$*_tmp_end=$*_end\
	--redefine-sym _binary_$*_tmp_size=$*_size\
	$(*).tmp $(@)
	echo "extern const u8" $(*)"[];" > $(*).h
	echo "extern const u32" $(*)_size[]";" >> $(*).h
	rm $(*).tmp
endef
 
#---------------------------------------------------------------------------------
%.o	:	%.mp3
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o) 
 
#---------------------------------------------------------------------------------
%.o	:	%.pcx
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)
 
#---------------------------------------------------------------------------------
%.o	:	%.bin
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)
 
#---------------------------------------------------------------------------------
%.o	:	%.png
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)

#---------------------------------------------------------------------------------
%.o	:	%.raw
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)
 
#---------------------------------------------------------------------------------
%.o	:	%.pal
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)
 
#---------------------------------------------------------------------------------
%.o	:	%.map
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)

#---------------------------------------------------------------------------------
%.o	:	%.mdl
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)

#---------------------------------------------------------------------------------
%.o	:	%.jpg
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)

#---------------------------------------------------------------------------------
%.o	:	%.mod
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)

#---------------------------------------------------------------------------------
%.o	:	%.gif
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)

#---------------------------------------------------------------------------------
%.o	:	%.txt
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)

#---------------------------------------------------------------------------------
%.o	:	%.bmp
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)

 
-include $(DEPENDS) 

#---------------------------------------------------------------------------------------
endif
   
lib:
	$(DEVKITPRO)/devkitARM/arm-eabi/bin/ar -cr test.a build/*.o

#---------------------------------------------------------------------------------------

#! /usr/bin/env python

import string
import codecs

def txt2csv_all(src, dest):
    txt2csv_game_kanji(src, dest)
    txt2csv_hiragana(src, dest)
    txt2csv_kanji(src, dest)
    txt2csv_katakana(src, dest)
    txt2csv_vocabulary_simple(src, dest)

def csv2txt_all(src, dest):
    csv2txt_game_kanji(src, dest)
    csv2txt_hiragana(src, dest)
    csv2txt_kanji(src, dest)
    csv2txt_katakana(src, dest)
    csv2txt_vocabulary_simple(src, dest)

def formatLine(line, length):
    return line.ljust(length,' ').replace('\n',' ').replace('\r',' ')

def csv2txt_game_kanji(src, dest):
    LINE_LENGTH=25

    csvFile=codecs.open(src+'game_kanji.csv', 'r', 'utf16')
    txtFile=codecs.open(dest+'game_kanji.txt', 'w', 'utf16')

    newLine=''
    
    for line in csvFile:
        newLine += formatLine(line,LINE_LENGTH)
        print line.ljust(LINE_LENGTH,' ')

    txtFile.write(newLine)
    
    csvFile.close()
    txtFile.close()

def csv2txt_hiragana(src, dest):
    SYLLABUS=5
    SAMPLE_ROMANJI=25
    SAMPLE_TRANSLATED=60
    SAMPLE_KANA=9

    csvFile=codecs.open(src+'hiragana.csv', 'r', 'utf16')
    txtFile=codecs.open(dest+'hiragana.txt', 'w', 'utf16')

    syllabus=''
    sampleRomanji=''
    sampleTranslated=''
    sampleKana=''
    newLine=''
    
    for line in csvFile:
        tableau = line.split('\t')
        syllabus = formatLine(tableau[0],SYLLABUS)
        sampleRomanji = formatLine(tableau[1],SAMPLE_ROMANJI)
        sampleTranslated = formatLine(tableau[2],SAMPLE_TRANSLATED)
        sampleKana = formatLine(tableau[3],SAMPLE_KANA)
        newLine += syllabus + sampleRomanji + sampleTranslated + sampleKana
        print syllabus + sampleRomanji + sampleTranslated + sampleKana

    txtFile.write(newLine)
    
    csvFile.close()
    txtFile.close()

def csv2txt_kanji(src, dest):
    MEANING=25
    KUN_YOMI=15
    ON_YOMI=15

    csvFile=codecs.open(src+'kanji.csv', 'r', 'utf16')
    txtFile=codecs.open(dest+'kanji.txt', 'w', 'utf16')

    meaning=''
    kunYomi=''
    onYomi=''
    newLine=''
    
    for line in csvFile:
        tableau = line.split('\t')
        meaning = formatLine(tableau[0],MEANING)
        kunYomi = formatLine(tableau[1],KUN_YOMI)
        onYomi = formatLine(tableau[2],ON_YOMI)
        newLine += meaning + kunYomi + onYomi
        print meaning + kunYomi + onYomi

    txtFile.write(newLine)
    
    csvFile.close()
    txtFile.close()

def csv2txt_katakana(src, dest):
    SYLLABUS=5
    SAMPLE_ROMANJI=25
    SAMPLE_TRANSLATED=60
    SAMPLE_KANA=9

    csvFile=codecs.open(src+'katakana.csv', 'r', 'utf16')
    txtFile=codecs.open(dest+'katakana.txt', 'w', 'utf16')

    syllabus=''
    sampleRomanji=''
    sampleTranslated=''
    sampleKana=''
    newLine=''
    
    for line in csvFile:
        tableau = line.split('\t')
        syllabus = formatLine(tableau[0],SYLLABUS)
        sampleRomanji = formatLine(tableau[1],SAMPLE_ROMANJI)
        sampleTranslated = formatLine(tableau[2],SAMPLE_TRANSLATED)
        sampleKana = formatLine(tableau[3],SAMPLE_KANA)
        newLine += syllabus + sampleRomanji + sampleTranslated + sampleKana
        print syllabus + sampleRomanji + sampleTranslated + sampleKana

    txtFile.write(newLine)
    
    csvFile.close()
    txtFile.close()

def csv2txt_vocabulary_simple(src, dest):
    ROMANJI=20
    JAPANESE=15
    MEANING=90

    csvFile=codecs.open(src+'vocabulary_simple.csv', 'r', 'utf16')
    txtFile=codecs.open(dest+'vocabulary_simple.txt', 'w', 'utf16')

    romanji=''
    japanese=''
    meaning=''
    newLine=''
    
    for line in csvFile:
        tableau = line.split('\t')
        romanji = formatLine(tableau[0],ROMANJI)
        japanese = formatLine(tableau[1],JAPANESE)
        meaning = formatLine(tableau[2],MEANING)
        newLine += romanji + japanese + meaning
        print romanji + japanese + meaning

    txtFile.write(newLine)
    
    csvFile.close()
    txtFile.close()

def txt2csv_game_kanji(src, dest):
    LINE_LENGTH=25
    
    txtFile=codecs.open(src+'game_kanji.txt', 'r', 'utf16')
    csvFile=codecs.open(dest+'game_kanji.csv', 'w', 'utf16')
    
    line=txtFile.read()
    nbLines=len(line)/LINE_LENGTH
    newLine=''
    
    for i in range(0,len(line),LINE_LENGTH):
        newLine += line[i:i+LINE_LENGTH].rstrip(u' ')+'\n'

    print newLine   
    csvFile.write(newLine)
    
    txtFile.close()
    csvFile.close()

def txt2csv_hiragana(src, dest):
    SYLLABUS=5
    SAMPLE_ROMANJI=25
    SAMPLE_TRANSLATED=60
    SAMPLE_KANA=9
    LINE_LENGTH=SYLLABUS+SAMPLE_ROMANJI+SAMPLE_TRANSLATED+SAMPLE_KANA
    
    txtFile=codecs.open(src+'hiragana.txt', 'r', 'utf16')
    csvFile=codecs.open(dest+'hiragana.csv', 'w', 'utf16')
    
    line=txtFile.read()
    nbLines=len(line)/LINE_LENGTH
    newLine=''
    
    for i in range(0,len(line),LINE_LENGTH):
        newLine += line[i:i+SYLLABUS].rstrip(u' ')+'\t'
        newLine += line[i+SYLLABUS:i+SYLLABUS+SAMPLE_ROMANJI].rstrip(u' ')+'\t'
        newLine += line[i+SYLLABUS+SAMPLE_ROMANJI:i+SYLLABUS+SAMPLE_ROMANJI+SAMPLE_TRANSLATED].rstrip(u' ')+'\t'
        newLine += line[i+SYLLABUS+SAMPLE_ROMANJI+SAMPLE_TRANSLATED:i+LINE_LENGTH].rstrip(u' ')+'\n'

    print newLine   
    csvFile.write(newLine)
    
    txtFile.close()
    csvFile.close()

def txt2csv_kanji(src, dest):
    MEANING=25
    KUN_YOMI=15
    ON_YOMI=15
    LINE_LENGTH=MEANING+KUN_YOMI+ON_YOMI
    
    txtFile=codecs.open(src+'kanji.txt', 'r', 'utf16')
    csvFile=codecs.open(dest+'kanji.csv', 'w', 'utf16')
    
    line=txtFile.read()
    nbLines=len(line)/LINE_LENGTH
    newLine=''
    
    for i in range(0,len(line),LINE_LENGTH):
        newLine += line[i:i+MEANING].rstrip(u' ')+'\t'
        newLine += line[i+MEANING:i+MEANING+KUN_YOMI].rstrip(u' ')+'\t'
        newLine += line[i+MEANING+KUN_YOMI:i+LINE_LENGTH].rstrip(u' ')+'\n'

    print newLine   
    csvFile.write(newLine)
    
    txtFile.close()
    csvFile.close()

def txt2csv_katakana(src, dest):
    SYLLABUS=5
    SAMPLE_ROMANJI=25
    SAMPLE_TRANSLATED=60
    SAMPLE_KANA=9
    LINE_LENGTH=SYLLABUS+SAMPLE_ROMANJI+SAMPLE_TRANSLATED+SAMPLE_KANA
    
    txtFile=codecs.open(src+'katakana.txt', 'r', 'utf16')
    csvFile=codecs.open(dest+'katakana.csv', 'w', 'utf16')
    
    line=txtFile.read()
    nbLines=len(line)/LINE_LENGTH
    newLine=''
    
    for i in range(0,len(line),LINE_LENGTH):
        newLine += line[i:i+SYLLABUS].rstrip(u' ')+'\t'
        newLine += line[i+SYLLABUS:i+SYLLABUS+SAMPLE_ROMANJI].rstrip(u' ')+'\t'
        newLine += line[i+SYLLABUS+SAMPLE_ROMANJI:i+SYLLABUS+SAMPLE_ROMANJI+SAMPLE_TRANSLATED].rstrip(u' ')+'\t'
        newLine += line[i+SYLLABUS+SAMPLE_ROMANJI+SAMPLE_TRANSLATED:i+LINE_LENGTH].rstrip(u' ')+'\n'

    print newLine   
    csvFile.write(newLine)
    
    txtFile.close()
    csvFile.close()

def txt2csv_vocabulary_simple(src, dest):
    ROMANJI_LENGTH=20
    JAPANESE_LENGTH=15
    MEANING_LENGTH=90
    LINE_LENGTH=ROMANJI_LENGTH+JAPANESE_LENGTH+MEANING_LENGTH
    
    txtFile=codecs.open(src+'vocabulary_simple.txt', 'r', 'utf16')
    csvFile=codecs.open(dest+'vocabulary_simple.csv', 'w', 'utf16')
    
    line=txtFile.read()
    nbLines=len(line)/LINE_LENGTH
    newLine=''
    
    for i in range(0,len(line),LINE_LENGTH):
        newLine += line[i:i+ROMANJI_LENGTH].rstrip(u' ')+'\t'
        newLine += line[i+ROMANJI_LENGTH:i+ROMANJI_LENGTH+JAPANESE_LENGTH].rstrip(u' ')+'\t'
        newLine += line[i+ROMANJI_LENGTH+JAPANESE_LENGTH:i+LINE_LENGTH].rstrip(u' ')+'\n'

    print newLine   
    csvFile.write(newLine)
    
    txtFile.close()
    csvFile.close()

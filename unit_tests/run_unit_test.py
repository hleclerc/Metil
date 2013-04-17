#! /usr/bin/python
# -*- coding: utf-8 -*-


import os
import stat
import sys
import time
import codecs


def main():
    nbreArgument=len(sys.argv)
    if(nbreArgument==1 or  nbreArgument== 2 or nbreArgument==3 ):
        t=Tests()
        t.run('report.html','reportcss.css')
        if ( t.GlobalResult):
            print " Unit tests Succeeded :-)"
            t.metAjourProduction()
        else:
            print " Unit tests has failed :-( ... "
    else:
        print '  erreur dans le nombre d\'arguments'
    
        
class ReportOfSourceFile:
    def __init__(self,logDir,fileNameCpp,compilReturn,erreurTestReturn):
	self.logDir=logDir
        self.fileNameCpp=fileNameCpp+'.cpp'
        self.fileName_log=fileNameCpp+'_result_compil'
        self.fileName_log_cerr=fileNameCpp+'_result_test'
	self.pathFile='../'+self.fileNameCpp
        
        if(compilReturn==0):
            self.compilResult=True
        else:
            self.compilResult=False
            
        if (erreurTestReturn==0):
            self.erreurTestResult=True
        else:
            self.erreurTestResult=False
            
class Utilitaires:
  
    def creerRepertoire(self,path,nomRepertoire):
        chemin=os.path.join(path,nomRepertoire)
        
        if not os.path.isdir(chemin):
            os.mkdir(chemin)
        #os.chdir(nomRepertoire)
    
    def create_html_link(self,href,text):
	return '<a href ="'+href+'">'+text+'</a>'
    
    def create_html_img(self,href,alt=''):
        return '<img src="'+href+'" alt="'+alt+'"/>'
    
    def testExistanceFichier(self,pathFileName):
        retour=0
        if os.path.isfile(os.path.join(pathFileName)):
            retour=1
        return retour
     
    def returnType(self,path): 
        mode=os.stat(path)[stat.ST_MODE]
        if stat.S_ISDIR(mode):
            return 'directory' 
        elif stat.S_ISREG(mode):
            return 'file'
        else:
            return ''
            
    def ecrireDansFichierLog(self,pathFileLog,pathFileTMP):
        if self.testExistanceFichier(pathFileLog):
            fichierLog=file (pathFileLog,'a')
        else:
            fichierLog=open(pathFileLog,'w')
            fichierLog.write( codecs.BOM_UTF8 )

        
        fichierTmp=open(pathFileTMP,'r')
        lignes=fichierTmp.readlines()
        fichierTmp.close()
        fichierLog.write('\n\r')
        heure=time.strftime('%d/%m/%y %H:%M',time.localtime()) 
        fichierLog.write(heure+'\n\r')
        for ligne in lignes:
            fichierLog.write(ligne)
        fichierLog.close()
        
    def returnLastIndexChar(self,path,char):
        i=0
        position=0
        
        while i<len(path):
            if path[i]==char:
                position=i
            i+=1
        return position
    
    def returnResultCompil(self,pathFile):
        fichier=open(pathFile,'r')
        lignes=fichier.readlines()
        fichier.close()
        contenuFichier=''
        for ligne in lignes:
            uneLigne=((ligne.rstrip('\n\r')).lstrip()).rstrip()
            
            if uneLigne!='':
                contenuFichier+=uneLigne
        
        if contenuFichier.find('.cpp')!=-1:
            return 1
        else:
            return 0
        
            
class Tests:
    def __init__(self):
        self.GlobalResult=True
        self.text=['FAIL','OK']
        self.command=''
        self.resultList=[]
        self.existFileTeste=False
        self.path_test=''
        self.fileLogCmpTmp='.logCmpTmp'
        self.fileLogTestTmp='.logTestTmp'
        self.nbreArgument=len(sys.argv)
        
        if self.nbreArgument==1:
            self.racine_appli=os.getcwd() 
            self.racine=self.donne_racine(self.racine_appli)
            
            
        else:
            self.racine_appli=sys.argv[1]
            self.racine =  self.racine_appli
            if Utilitaires().returnType(sys.argv[2])=='directory':
                self.path_test=sys.argv[2]
            elif Utilitaires().returnType(sys.argv[2])=='file':
                position= Utilitaires().returnLastIndexChar(sys.argv[2],'/')
                self.path_test=sys.argv[2][0:position]
        self.nomDuProgramme=self.recupeNomDUProgramme(self.racine)
        
                
        
        self.img=['images/no.png','images/ok.png']
        self.repertoireLog='.log'
                
    def donne_racine(self, rep):
        os.chdir( '..' )
        racine = os.getcwd()
        os.chdir(rep)
        return racine
    
    def find_and_exec(self,path):
            
                
        #self.GlobalResult = False
        for dir in os.listdir(path):
            if(dir[0]!='.'):
                
                pathName=os.path.join(path,dir)
                
                if Utilitaires().returnType(pathName)=='directory':
                    self.find_and_exec(pathName)
                elif (Utilitaires().returnType(pathName)=='file' and dir.endswith('.cpp') and dir.find('_test')!=-1):
                    fileName=dir[:-4]
                    fileName_log=fileName+'_result_compil'
                    fileName_log_cerr=fileName+'_result_test'
                    
                    Utilitaires().creerRepertoire(self.racine_appli,self.repertoireLog)
                    
                    command=' metil_comp   -lboost_unit_test_framework '+pathName+' 2>'+os.path.join(os.path.join(self.racine_appli,self.repertoireLog),self.fileLogCmpTmp)
                    
                    self.existFileTeste=True
                    os.system(command)
                    
                    compile_res=Utilitaires().returnResultCompil(os.path.join(os.path.join(self.racine_appli,self.repertoireLog),self.fileLogCmpTmp))
                    Utilitaires().ecrireDansFichierLog(os.path.join(os.path.join(self.racine_appli,self.repertoireLog),fileName_log)
                                        ,os.path.join(os.path.join(self.racine_appli,self.repertoireLog),self.fileLogCmpTmp))
                    if(compile_res==0):
                        
                        index=len(dir)
                        rep=pathName[:-index]
                        os.chdir(os.path.join(rep,'compilations'))
                        
                        command='./'+( pathName.replace( "/", "_" ) ).replace( ".cpp", "_cpp.exe" )+'>'+os.path.join(os.path.join(self.racine_appli,self.repertoireLog),self.fileLogTestTmp)
                        erreurTest=os.system(command)
			
                        if(erreurTest!=0):
			    
                            self.GlobalResult=False
                        os.chdir(self.racine_appli)
                    else:
                        
                        erreurTest=200
                        fichier=file(os.path.join(os.path.join(self.racine_appli,self.repertoireLog),self.fileLogTestTmp),'w')
                        fichier.write('Test non réalisé cause erreurs dans la compilation ')
                        fichier.close()
                      
                    Utilitaires().ecrireDansFichierLog(os.path.join(os.path.join(self.racine_appli,self.repertoireLog),fileName_log_cerr),os.path.join(os.path.join(self.racine_appli,self.repertoireLog),self.fileLogTestTmp))
                        
                    r=ReportOfSourceFile(os.path.join('../',self.repertoireLog),fileName,compile_res,erreurTest)
                    self.resultList.append(r)
                    
       
    def recupeNomDUProgramme(self,path):
        liste=path.split('/')
        #indexDebut= path.index('/',1)  
        #return path[indexDebut+1:-1]
        return liste[len(liste)-1]
    
         
    def donneEnteteHtml(self):
        enteteHtml='<html>\n<head>\n'
        enteteHtml+='<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />'
        enteteHtml+='<link rel="stylesheet" type="text/css" href="reportcss.css">'
        enteteHtml+='</head><body>'
        return enteteHtml
    
    def donneFooterHtml(self):
        footerHtml='</table></div></body></html>'
        return footerHtml
    
    def donneEnteteTable(self):
        enteteTable='\t<tr>\n\t\t<th class="file text"> Source File Test </th>'
        enteteTable+= '<th class="result text"  > Compilation </th> <th class="report text" >'
        enteteTable+= 'Log File </th> <th class="result text"  >Test Result  </th>'
        enteteTable+= '<th class="report text"> Log Cerr File </th>\n\t</tr>\n'
        return enteteTable
    
    def donneLigneTable(self,r):
        ligneTable='\t<tr class="file">\n\t\t<td>'+Utilitaires().create_html_link(r.pathFile,r.fileNameCpp)+'</td>'
        ligneTable+='<td class="result center">'+Utilitaires().create_html_img(self.img[r.compilResult], self.text[r.compilResult]) +'</td>'
        ligneTable+='<td class="report center">'+Utilitaires().create_html_link(os.path.join(r.logDir,r.fileName_log),r.fileName_log)+'</td>'
        ligneTable+='<td class="result center">'+ Utilitaires().create_html_img(self.img[r.erreurTestResult], self.text[r.erreurTestResult]) +'</td>'
        ligneTable+='<td class="report center">'+Utilitaires().create_html_link(os.path.join(r.logDir,r.fileName_log_cerr),r.fileName_log_cerr)+'</td>'
        return ligneTable
                
    def genererFichierCSS( self,fileNameCss ):
        css=file( fileNameCss,'w' )
        css.write( 'table{\ncellpadding:2;\n width :80% ;\n cellspacing:1;\n border:0;\n}\n' )
        css.write( '\n th {\nfont-family: monospace;\n padding: 5px;\n background-color: #D0E3FA;\n}\n\n' )
        css.write( '.file{\n width:35%;\n text-align:left;\n}\n\n' )
        css.write( '.result{\n width:10%;\n}\n\n' )
        css.write( '.report{\n width:20%;\n}\n\n' )
        css.write( '.label{\n font-family:serif;\nfont-size: 18px;\n}\n\n' )
        css.write( '.center{\ntext-align:center;\n}\n\n' )
        css.write( '.espace20{\n margin-top:20px;\n}\n\n' )
        css.write( '.retrait20{\n margin-left:20px;\n}\n\n' )
        css.write( '.text{\n font-family:serif;\n font-size: 16px;\n}\n\n' )
        css.write( '.entete{\n background-color:#046380;\n border-radius:7px;\n -moz-border-radius:7px;\n -webkit-border-radius:7px;\n padding:7px;\n color:white;\n}\n\n' )
        css.write( 'a{\n text-decoration:none;\n}\n\n' )
        css.close()
        
    def metAjourProduction(self):

	os.chdir( '..' ) 
	os.chdir( '..' ) 
	os.system( ' make push_production_if_valid' )
	
         
    def run(self,fileNameReportHtml,fileNameCss):
        if self.path_test!='':
            path=self.path_test
        else:
            path=self.racine_appli
        self.find_and_exec(path)
        Utilitaires().creerRepertoire(self.racine_appli,'html')
        os.chdir(os.path.join(self.racine_appli,'html'))
        html=file(fileNameReportHtml,'w')
        if (self.existFileTeste==True):
            
            html.write(self.donneEnteteHtml())
            html.write('<div class="center espace20 entete"><span class="label"> RAPPORT DES TESTS  </span> </div> ')
            html.write('<div class="center espace20"><span class="label"> Nom du Programme  :</span>  '+self.nomDuProgramme+'</div>')
            html.write('<div class="retrait20 espace20"><span class="label">Global Result  : </span> '
                       +Utilitaires().create_html_img( self.img[self.GlobalResult], self.text[self.GlobalResult])+'</div>')
            html.write('<div class="retrait20 espace20"><span class="label">Results  :</span></div>')
            html.write('<div class="center" retrait20 espace 20"><table>')
            html.write( self.donneEnteteTable())
            
            for r in self.resultList:
                html.write(self.donneLigneTable(r))
            
            html.write(self.donneFooterHtml())
            
            self.genererFichierCSS(fileNameCss)
        else:
            html.write('<div>aucun fichier test trouv�</div>')
        html.close()
        
    
            
main()
            
            

  

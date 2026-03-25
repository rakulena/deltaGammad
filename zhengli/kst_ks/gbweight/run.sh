if [ ! $# -eq 1  ];then
   echo param error!
   exit 1
fi

mode=$1

if [ "$mode" == "reso" ];then
   python3.10 weight_reso_prompt.py 1516 
   python3.10 weight_reso_prompt.py 2017 
   python3.10 weight_reso_prompt.py 2018   
fi

if [ "$mode" == "tacc" ];then
   python3.10 weight_tacc_bdjpsikst.py 1516  
   python3.10 weight_tacc_bdjpsikst.py 2017 
   python3.10 weight_tacc_bdjpsikst.py 2018 
fi

if [ "$mode" == "anga" ];then
   python3.10 weight_anga_bdjpsipipi.py 1516  
   python3.10 weight_anga_bdjpsipipi.py 2017 
   python3.10 weight_anga_bdjpsipipi.py 2018 
fi


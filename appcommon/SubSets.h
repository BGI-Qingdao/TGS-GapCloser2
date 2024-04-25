#ifndef __APPCOMMON_SUBSETS_H__
#define __APPCOMMON_SUBSETS_H__
#include <map>
#include <cassert>
namespace BGIQD {
    namespace SUBSETS {

        struct SubSets
        {
            void Push( int start , int end ,int curr_scaff_id, int curr_gap_id)
            {
                assert( start <= end );
                if( ranges.find(start ) == ranges.end()) 
                    ranges[start] =end ;
                else
                    if( ranges.at(start) < end )
                        ranges[start] =end ;
                clean_overlap();
                scaff_id = curr_scaff_id;
                gap_id = curr_gap_id;
            }

            bool Pop( int & start , int & end )
            {
                if( ranges.empty() )
                    return false ;
                else
                {
                    auto pair = *ranges.begin() ;
                    start = pair.first ; 
                    end = pair.second ;
                    ranges.erase(ranges.begin());
                    return true ;
                }
            }

            int scaff_id;
            int gap_id;
            private:
            std::map<int , int > ranges;
            
            void clean_overlap()
            {
                while(true)
                {
                    if( ranges.size() < 2 )
                        break;
                    bool updated = false ;
                    auto itr = ranges.begin() ;
                    auto itr1 = std::next(itr);
                    for(int i = 0 ; i< (int) ranges.size() -1 ; i ++ )
                    {
                        assert(itr->first < itr1->first);
                        if(itr->second >= itr1->first) 
                        {
                            if( itr1->second > itr->second )
                                itr->second =  itr1->second ;
                            ranges.erase(itr1);
                            updated = true ;
                            break;
                        }
                        itr=itr1;
                        itr1 = std::next(itr1);
                    }
                    if(!updated)
                        break;
                }
            }
        };
    }
}
#endif

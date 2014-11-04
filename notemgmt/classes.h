//STL
#include <vector>
#include <algorithm>

using namespace std;

class ノート経営 {
	public:
		ノート経営() {
			//しません。
			レゾリューション = 192;
		};

		ノート経営(unsigned int プレイヤー) {
			データ.resize(プレイヤー);
			レゾリューション = 192;
		};

		void セットレゾリューション(unsigned int a) {
			レゾリューション = a;
		}

		void 片付ける() {
			//vectorのサイズはゼロです。
			データ.clear();
		}

		void プレイヤー片付ける(unsigned int プレイヤー) {
			データ[プレイヤー].clear();
		}

		void セットプレイヤーカウント(int プレイヤー) {
			データ.resize(プレイヤー);
		}

		void push_back_note(int プレイヤー, int 位置, int 色, int サステイン, int キーサウンド) {
			//This is a special "push_back". It accepts 5 arguments rather than 1 and adds it to a private class.
			データ[プレイヤー].push_back(ノート(位置, 色, サステイン, キーサウンド));
		}

		void push_back_bpm(int 位置, int テン) {
			//This is a special "push_back". It accepts 2 arguments rather than 1 and adds it to a private class.
			BPM.push_back(テンポ(位置, テン));
		}

		unsigned int プレイヤーカウント() {
			//Vectorのデータのサイズを返します。
			return データ.size();
		}

		unsigned int プレイヤーデータカウント(unsigned int プレイヤー) {
			//Vectorのデータのプレイヤーのサイズを返します。
			return データ[プレイヤー].size();
		}

		unsigned int テンポカウント() {
			//VectorのBPMのサイズを返します。
			return BPM.size();
		}
		
		void チャートプリペア() {
			//BPMを割り出しています
			calcPosBPM();

			//ノートを割り出しています
			for (int i = 0; i < プレイヤーカウント(); i++) {
				calcPosノート(i);
			}
		}

		int ノート位置(unsigned int プレイヤー, unsigned int ノート) {
			return データ[プレイヤー][ノート].ノート位置();
		}

		int ノート色(unsigned int プレイヤー, unsigned int ノート) {
			return データ[プレイヤー][ノート].ノート色();
		}

		int ノートサステイン(unsigned int プレイヤー, unsigned int ノート) {
			return データ[プレイヤー][ノート].ノートサステイン();
		}

		int ノートキーサウンド(unsigned int プレイヤー, unsigned int ノート) {
			return データ[プレイヤー][ノート].ノートキーサウンド();
		}

		double ノートMS(unsigned int プレイヤー, unsigned int ノート) {
			return データ[プレイヤー][ノート].ノートMS();
		}

		void ソートノート(unsigned int プレイヤー) {
			sort(データ[プレイヤー].begin(), データ[プレイヤー].end());
		}

		void すべてのソートノート() {
			for (int i = 0; i < プレイヤーカウント(); i++) {
				ソートノート(i);
			}
		}
	private:
		class ノート {
			public:
				ノート() {
					位置			= 0;
					MS			= 0;
					色			= 0;
					サステイン	= 0;
					キーサウンド	= 0;
				};

				ノート(int a, int b, int c, int d) {
					位置			= a;
					MS			= 0;
					色			= b;
					サステイン	= c;
					キーサウンド	= d;
				};

				//Set
				void セットMS(int a)	{ MS = a;	}

				//Get
				int ノート位置()				{ return 位置;			}
				int ノート色()				{ return 色;				}
				int ノートサステイン()		{ return サステイン;		}
				int ノートキーサウンド()		{ return キーサウンド;	}
				double ノートMS()			{ return MS;			}

				//Overloads
				bool operator<(ノート &a) {
					if (ノート位置() == a.ノート位置()) {
						return ノート色() < a.ノート色();
					}
					return (ノート位置() < a.ノート位置());
				}

				bool operator>(ノート &a) {
					if (ノート位置() == a.ノート位置()) {
						return ノート色() > a.ノート色();
					}
					return (ノート位置() > a.ノート位置());
				}

				bool operator==(ノート &a) {
					return (ノート位置() == a.ノート位置() && ノート色() == a.ノート色());
				}
			private:
				int 位置;
				double MS;
				int 色;
				int サステイン;
				int キーサウンド;
		};

		class テンポ {
			public: 
				テンポ() {
					//しません
				};

				テンポ(int a, double b) {
					位置 = a;
					BPM = b;
				};

				//Set
				void セットMS(double a)	{ MS = a;	}

				//Get
				int テンポ位置()			{ return 位置;	}
				double テンポBPM()		{ return BPM;	}
				double テンポMS()		{ return MS;	}
				
				//Overloads
				bool operator<(テンポ &a) {
					return (テンポ位置() < a.テンポ位置());
				}

				bool operator>(テンポ &a) {
					return (テンポ位置() > a.テンポ位置());
				}

			private: 
				int 位置;
				double BPM;
				double MS;
		};

		bool 未満(ノート a, ノート b) {
			return (a.ノート位置() < b.ノート位置());
		}

		void calcPosBPM() {
			//テンポのMS位置を割り出しています。
			int pos = 0;
			sort(BPM.begin(), BPM.end()); //今、ソートです。
			for (unsigned int i = 0; i < BPM.size(); i++) {
				if (i == 0)
					BPM[i].セットMS(0);
				else
					BPM[i].セットMS(((60000.00 / (BPM[i - 1].テンポBPM() / 1000)) * ((double)(BPM[i].テンポ位置() - BPM[i - 1].テンポ位置()) / レゾリューション)) + BPM[i - 1].テンポMS());
			}
		}

		void calcPosノート(unsigned int プレイヤー) {
			//ノートのMS位置を割り出しています。
			unsigned int cur_bpm = 0;
			ソートノート(プレイヤー); //今、ソートです。

			for (unsigned int i = 0; i < プレイヤーデータカウント(プレイヤー); i++) {
				//BPMの尋ねります。
				if (cur_bpm < テンポカウント() - 1)
					while (BPM[cur_bpm + 1].テンポ位置() < データ[プレイヤー][i].ノート位置()) {
						cur_bpm++;
						if (cur_bpm >= テンポカウント() - 1)
							break;
					}

				データ[プレイヤー][i].セットMS(((60000.00 / (BPM[cur_bpm].テンポBPM() / 1000)) * ((double)(データ[プレイヤー][i].ノート位置() - BPM[cur_bpm].テンポ位置()) / レゾリューション)) + BPM[cur_bpm].テンポMS());
			}
		}

		//データは二次元Vectorですね。VectorのVectorです。
		vector< vector<ノート> > データ;
		vector< テンポ > BPM;
		int レゾリューション;
};
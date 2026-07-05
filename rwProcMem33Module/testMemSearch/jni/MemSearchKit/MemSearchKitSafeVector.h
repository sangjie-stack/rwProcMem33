//
// Created by abcz316 on 2020/6/25.
//

#ifndef MEM_SEARCH_KIT_SAFE_VECTOR_H
#define MEM_SEARCH_KIT_SAFE_VECTOR_H
#include <vector>
#include <iterator>
#include <mutex>
#include <algorithm>
#include <atomic>
#include <assert.h>
<<<<<<< HEAD

#ifndef min
#define min(a,b) (((a)<(b))?(a):(b))
#endif

=======
>>>>>>> 77f65634a89680148d5d23e35132cc9fda6712df
template<typename T> struct MemSearchSafeVector {
	MemSearchSafeVector() {}
	MemSearchSafeVector(const std::vector<T> vBlock) {
		std::lock_guard<std::mutex> mlock(m_lockBlockAccess);
		m_vBlock.assign(vBlock.begin(), vBlock.end());
	}
<<<<<<< HEAD
	//ï¿½ï¿½ï¿½
=======
	//Çå¿Õ
>>>>>>> 77f65634a89680148d5d23e35132cc9fda6712df
	void clear() {
		std::lock_guard<std::mutex> mlock(m_lockBlockAccess);
		m_vBlock.clear();
		m_nFastBlockCount = 0;
	}
<<<<<<< HEAD
	//ï¿½ï¿½È¡ï¿½ï¿½ï¿½ï¿½ï¿½Ð¡
	size_t size() {
		return m_nFastBlockCount;
	}
	//ï¿½ï¿½ï¿½ï¿½Ò»ï¿½ï¿½ï¿½ï¿½Ô±
=======
	//»ñÈ¡Êý×é´óÐ¡
	size_t size() {
		return m_nFastBlockCount;
	}
	//Ìí¼ÓÒ»¸ö³ÉÔ±
>>>>>>> 77f65634a89680148d5d23e35132cc9fda6712df
	bool push_back(const T& in) {
		std::lock_guard<std::mutex> mlock(m_lockBlockAccess);
		m_vBlock.push_back(in);
		m_nFastBlockCount++;
		return true;
	}
<<<<<<< HEAD
	//ï¿½ï¿½È¡Ò»ï¿½ï¿½ï¿½ï¿½Ô±
=======
	//»ñÈ¡Ò»¸ö³ÉÔ±
>>>>>>> 77f65634a89680148d5d23e35132cc9fda6712df
	bool pop_back(T& out) {
		std::lock_guard<std::mutex> mlock(m_lockBlockAccess);
		if (!m_vBlock.size()) {
			return false;
		}
		out = m_vBlock.back();
		m_vBlock.pop_back();
		m_nFastBlockCount--;
		return true;
	}
<<<<<<< HEAD
	bool pop_back(size_t get_cnt, std::vector<T>& vOut) {
		std::lock_guard<std::mutex> mlock(m_lockBlockAccess);
		if (!m_vBlock.size()) {
			return false;
		}
		vOut.clear();
		size_t realPopCnt = min(get_cnt, m_vBlock.size());
		for (; realPopCnt > 0; realPopCnt--) {
=======
	//»ñÈ¡Ò»¸ö³ÉÔ±
	bool pop_back(size_t get_cnt, std::vector<T>& vOut) {
		std::lock_guard<std::mutex> mlock(m_lockBlockAccess);
		if (get_cnt > m_vBlock.size()) {
			return false;
		}
		vOut.clear();
		for (; get_cnt > 0; get_cnt--) {
			if (!m_vBlock.size()) {
				break;
			}
>>>>>>> 77f65634a89680148d5d23e35132cc9fda6712df
			auto out_obj = m_vBlock.back();
			m_vBlock.pop_back();
			vOut.push_back(out_obj);
			m_nFastBlockCount--;
		}
		return true;
	}
<<<<<<< HEAD
	//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ô±
=======
	//¿½±´³ÉÔ±
>>>>>>> 77f65634a89680148d5d23e35132cc9fda6712df
	void copy_vals_to(std::vector<T>& vOut) {
		std::lock_guard<std::mutex> mlock(m_lockBlockAccess);
		vOut.clear();
		vOut.assign(m_vBlock.begin(), m_vBlock.end());
	}
	void copy_vals_to(MemSearchSafeVector& targetMemSearchSafeVector) {
		std::lock_guard<std::mutex> mlock(m_lockBlockAccess);
		targetMemSearchSafeVector.clean();
		for (auto& item : m_vBlock) {
			targetMemSearchSafeVector.push_back(item);
		}
	}
	void assign(MemSearchSafeVector& src) {
		std::lock_guard<std::mutex> mlock(m_lockBlockAccess);
		m_vBlock.assign(src.begin(), src.end());
	}
<<<<<<< HEAD
	//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Â±ï¿½ï¿½È¡ï¿½ï¿½Ô±ï¿½ï¿½ï¿½ï¿½
=======
	//¸ù¾ÝÊý×éÏÂ±ê»ñÈ¡³ÉÔ±¶ÔÏó
>>>>>>> 77f65634a89680148d5d23e35132cc9fda6712df
	const T& at(size_t i) {
		std::lock_guard<std::mutex> mlock(m_lockBlockAccess);
		assert(i < m_nFastBlockCount);
		return m_vBlock.at(i);
	}
<<<<<<< HEAD
	//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
=======
	//Êý×éÅÅÐò
>>>>>>> 77f65634a89680148d5d23e35132cc9fda6712df
	void sort(bool func(const T& a, const T& b)) {
		std::lock_guard<std::mutex> mlock(m_lockBlockAccess);
		std::sort(m_vBlock.begin(), m_vBlock.end(), func);
	}
	auto begin() {
		std::lock_guard<std::mutex> mlock(m_lockBlockAccess);
		return m_vBlock.begin();
	}
	auto end() {
		std::lock_guard<std::mutex> mlock(m_lockBlockAccess);
		return m_vBlock.end();
	}
private:
	std::vector<T> m_vBlock;
	std::atomic<size_t> m_nFastBlockCount{ 0 };
	std::mutex m_lockBlockAccess;
};


#endif //MEM_SEARCH_KIT_SAFE_VECTOR_H

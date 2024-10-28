--Câu 1: Liệt kê danh sách họ tên và mã độc giả người lớn đang mượn sách chưa trả
--và số lượng sách họ đang mượn
--==============================================
declare @MaNguoiLon as table (ma_docgia int)
insert into @MaNguoiLon
select
	ma_docgia
from nguoilon
select
	concat(dg.ho, ' ', dg.tenlot, ' ', dg.ten) hovaten
	, dg.ma_docgia
	, sl.sl_dangmuon
from docgia dg
join
	(select
		count(m.ma_docgia) sl_dangmuon,
		m.ma_docgia
	from muon m
	left join qtrinhmuon qtm
	on qtm.ma_cuonsach = m.ma_cuonsach
	and qtm.ma_docgia = m.ma_docgia
	and qtm.ngay_muon = m.ngay_muon
	and qtm.ngay_hethan = m.ngay_hethan
	where 1 = 1
	and qtm.isbn is null
	and m.ma_docgia in (select ma_docgia from @MaNguoiLon)
	group by m.ma_docgia
	) sl
on sl.ma_docgia = dg.ma_docgia

--==============================================

--Câu 2: Liệt kê danh sách họ tên và mã độc giả người lớn đang mượn sách trể hạn (so với quy định)
--==============================================
declare @MaNguoiLon as table (ma_docgia int)
insert into @MaNguoiLon
select
	ma_docgia
from nguoilon
select
	concat(dg.ho, ' ', dg.tenlot, ' ', dg.ten) hovaten
	, dg.ma_docgia
from docgia dg
join
	(select
		m.ma_docgia
	from muon m
	left join qtrinhmuon qtm
	on qtm.ma_cuonsach = m.ma_cuonsach
	and qtm.ma_docgia = m.ma_docgia
	and qtm.ngay_muon = m.ngay_muon
	and qtm.ngay_hethan = m.ngay_hethan
	where qtm.isbn is null
	and m.ngay_hethan < getdate()
	and m.ma_docgia in (select ma_docgia from @MaNguoiLon)
	) tre
on tre.ma_docgia = dg.ma_docgia
--==============================================

--Câu 3: Liệt kê danh sách họ tên đọc giả trẻ em đang mượn sách chưa trả
--và tên đầu sách mà trẻ em đang mượn
--==============================================
declare @MaTreEm as table (ma_docgia int)
insert into @MaTreEm
select
	ma_docgia
from treem
select
	concat(dg.ho, ' ', dg.tenlot, ' ', dg.ten) hovaten
	, dg.ma_docgia
	, tsa.tuasach
from docgia dg
join
	(select
		ts.tuasach,
		m.ma_docgia
	from muon m
	left join qtrinhmuon qtm
	on qtm.ma_cuonsach = m.ma_cuonsach
	and qtm.ma_docgia = m.ma_docgia
	and qtm.ngay_muon = m.ngay_muon
	and qtm.ngay_hethan = m.ngay_hethan
	join dausach ds
	on ds.isbn = m.isbn
	join tuasach ts
	on ts.ma_tuasach = ds.ma_tuasach
	where qtm.isbn is null
	and m.ma_docgia in (select ma_docgia from @MaTreEm)
	) tsa
on tsa.ma_docgia = dg.ma_docgia
--==============================================

--Câu 4: Liệt kê danh sách các độc giả người lớn đang mượn sách chưa trả đồng thời trẻ em mà người
--lớn đó đang bảo lãnh cũng có mượn sách chưa trả.
--==============================================
declare @MaChuaTra as table (ma_docgia int)
insert into @MaChuaTra
select
	m.ma_docgia
from muon m
left join qtrinhmuon qtm
on qtm.ma_cuonsach = m.ma_cuonsach
and qtm.ma_docgia = m.ma_docgia
and qtm.ngay_muon = m.ngay_muon
and qtm.ngay_hethan = m.ngay_hethan
where qtm.isbn is null

select
	concat(dg.ho, ' ', dg.tenlot, ' ', dg.ten) hovaten
	, dg.ma_docgia
from docgia dg
join treem te
on te.ma_docgia_nguoilon = dg.ma_docgia
where 1 = 1
and te.ma_docgia in (select ma_docgia from @MaChuaTra)
and te.ma_docgia_nguoilon in (select ma_docgia from @MaChuaTra)
--==============================================

--Câu 5: Liệt kê danh sách độc giả đang đăng ký mượn sách mà tên đầu sách cần mượn
--==============================================
select
	concat(dg.ho, ' ', dg.tenlot, ' ', dg.ten) hovaten
	, dg.ma_docgia
	, ts.tuasach
from docgia dg
join dangky dk
on dk.ma_docgia = dg.ma_docgia
join dausach ds
on ds.isbn = dk.isbn
join tuasach ts
on ts.ma_tuasach = ds.ma_tuasach
--==============================================

--Câu 6: Liệt kê danh sách độc giả đang đăng ký mượn sách và số lượng đầu sách đã đăng ký.
--==============================================
select
	concat(dg.ho, ' ', dg.tenlot, ' ', dg.ten) hovaten
	, dg.ma_docgia
	, sl.sl_dk
from docgia dg
join 
	(select
	   ma_docgia
	   ,count (ma_docgia) sl_dk
	from dangky
	group by ma_docgia
	) sl
on sl.ma_docgia = dg.ma_docgia
--==============================================

--Câu 7: Liệt kê danh sách mã isbn và tên đầu sách đang được độc giả đăng ký mượn và đang trong
--trạng thái sẵn sàng cho mượn
--==============================================
select
	distinct dk.isbn
	, ts.tuasach
from dangky dk
join dausach ds
on ds.isbn = dk.isbn
join tuasach ts
on ts.ma_tuasach = ds.ma_tuasach
where 1 = 1
and lower(ds.trangthai) = 'y'
--==============================================

--Câu 8: Với mỗi đầu sách, cho biết số lần đã mượn (và đã trả)
--==============================================
select
*
from
(	select
		isbn
		,count (isbn) sl_muon
	from muon
	group by isbn
) slmuon
full outer join
(
	select
		m.isbn
		,count (m.isbn) sl_tra
	from muon m
	right join qtrinhmuon qtm
	on qtm.ma_cuonsach = m.ma_cuonsach
	and qtm.ma_docgia = m.ma_docgia
	and qtm.ngay_muon = m.ngay_muon
	and qtm.ngay_hethan = m.ngay_hethan
	group by m.isbn
) sltra
on slmuon.isbn = sltra.isbn
--==============================================